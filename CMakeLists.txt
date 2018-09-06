cmake_minimum_required(VERSION 3.9)
INCLUDE("functions.cmake")
set(CMAKE_CXX_STANDARD 14)

# Load hardware target profiles
SET(TARGET_EXTERNAL_LIBS)
LOAD_CMAKEFILES_IN_DIR("target")
project(LittleGUI)

# Build code in these dirs
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
