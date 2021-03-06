##### Macros #####
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

#### Functions #####
FUNCTION(LOAD_CMAKEFILES_IN_DIR dirName)
    MESSAGE("++ Loading all CMake files in the dir: ${dirName}")
    FILE(GLOB cmakeFiles ${dirName}/*/CMakeLists.txt)
    FOREACH(cmakeFile ${cmakeFiles})
        MESSAGE("++ Including: ${cmakeFile}")
        INCLUDE(${cmakeFile})
    ENDFOREACH(cmakeFile)
ENDFUNCTION(LOAD_CMAKEFILES_IN_DIR)

FUNCTION(ADD_DIRS_IN_DIR dirName)
    SUBDIRLIST("SUBDIRS" ${dirName})
    FOREACH(subdir ${SUBDIRS})
        ADD_SUBDIRECTORY(${subdir})
    ENDFOREACH(subdir)
ENDFUNCTION(ADD_DIRS_IN_DIR)