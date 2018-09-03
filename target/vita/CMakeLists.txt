message("** Configuring toolchain for Vita")

## ------------    VITA Functions  ---------
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

## ------------ VITA Configuration ----------
## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else ()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif ()
endif ()

# List of basic PS Vita external libs required by the lib
list(INSERT
        TARGET_EXTERNAL_LIBS
        vita2d
        SceDisplay_stub # Required by: vita2d
        SceGxm_stub # Required by: vita2d
        SceCommonDialog_stub # Required by: vita2d
        SceSysmodule_stub # Required by: vita2d
        SceTouch_stub
        SceCtrl_stub
        png
        jpeg
        z # required by png for crc32
        SceNet_stub
        SceNetCtl_stub
        freetype
        ScePower_stub
        SceRegistryMgr_stub)


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

    if (DEBUGNET)
        add_definitions(-g)
        add_definitions(-DDEBUGNET)
        target_link_libraries(${APP_NAME} debugnet)
        file(STRINGS "debugnetip.txt" DEBUGNETIP)
        add_definitions(-DDEBUGNETIP="${DEBUGNETIP}")
        message("++ DEBUGNET is on. Your app will be sending msg to ${DEBUGNETIP}.")
    endif ()

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
