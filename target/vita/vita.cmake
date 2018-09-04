## Build and link
# Add all the files needed to compile here
FUNCTION(ADD_RESOURCES out_var)
    SET(result)
    FOREACH (in_f ${ARGN})
        SET(out_f "${CMAKE_CURRENT_BINARY_DIR}/${in_f}.o")
        GET_FILENAME_COMPONENT(out_dir ${out_f} DIRECTORY)
        ADD_CUSTOM_COMMAND(OUTPUT ${out_f}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${out_dir}
                COMMAND ${CMAKE_LINKER} -r -b binary -o ${out_f} ${in_f}
                DEPENDS ${in_f}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Building resource ${out_f}"
                VERBATIM
                )
        LIST(APPEND result ${out_f})
    ENDFOREACH ()
    SET(${out_var} "${result}" PARENT_SCOPE)
ENDFUNCTION()

MACRO(INIT_VITA_BUILD TITLE_ID)
    # This line adds Vita helper macros, must go after project definition in order
    # to build Vita specific artifacts (self/vpk).
    include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

    ## Configuration options for this app
    # Display name (under bubble in LiveArea)
    set(VITA_APP_NAME ${APP_NAME})

    # Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
    # unique string of developer and Y = a unique number for this app
    set(VITA_TITLEID TITLE_ID)

    add_definitions(-DVITA_TITLEID="${VITA_TITLEID}")

    # Optional version string to show in LiveArea's more info screen
    option(DEBUGNET "Enable debugnet for logging" ON)

    if (CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("++ Debug build enabled")
        if (DEBUGNET)
            add_definitions(-DDEBUGNET)
            target_link_libraries(${APP_NAME} debugnet)
            file(STRINGS "debugnetip.txt" DEBUGNETIP)
            add_definitions(-DDEBUGNETIP="${DEBUGNETIP}")
            message("++ DEBUGNET is on. Your app will be sending msg to ${DEBUGNETIP}.")
        endif ()
    else(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("++ Release build - Run cmake -DCMAKE_BUILD_TYPE=Debug .. to enable debugging")
    endif (CMAKE_BUILD_TYPE MATCHES DEBUG)



    ## Flags and includes for building
    # Note that we make sure not to overwrite previous flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

    # Optional. You can specify more param.sfo flags this way.
    set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

    file(GLOB_RECURSE res_files RELATIVE ${CMAKE_SOURCE_DIR} assets/*.png assets/*.jpeg assets/*.yml assets/*.ttf assets/*.wav assets/*.ogg)
    add_resources(PROJECT_RESOURCES ${res_files})
ENDMACRO(INIT_VITA_BUILD)

FUNCTION(BUILD_VPK VITA_VERSION, VPK_BUNDLED_FILES)
    vita_create_self(${APP_NAME}.self ${APP_NAME})
    vita_create_vpk(${APP_NAME}.vpk ${VITA_TITLEID} ${APP_NAME}.self
            VERSION ${VITA_VERSION}
            NAME ${VITA_APP_NAME}
            ${VPK_BUNDLED_FILES})

ENDFUNCTION(BUILD_VPK)
