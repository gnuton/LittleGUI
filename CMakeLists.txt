cmake_minimum_required(VERSION 3.12)
INCLUDE("functions.cmake")
set(CMAKE_CXX_STANDARD 14)

# Load hardware profiles
LOAD_CMAKEFILES_IN_DIR("hw")
project(LittleGUI)

# Build code in these dirs
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)