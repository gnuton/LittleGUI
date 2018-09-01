#### Functions #####
function(LOAD_CMAKEFILES_IN_DIR dirName)
    message("++ Loading all CMake files in the dir: ${dirName}")
    file(GLOB cmakeFiles ${dirName}/*/CMakeLists.txt)
    foreach(cmakeFile ${cmakeFiles})
        message("++ Including: ${cmakeFile}")
        INCLUDE(${cmakeFile})
    endforeach(cmakeFile)
endfunction(LOAD_CMAKEFILES_IN_DIR)