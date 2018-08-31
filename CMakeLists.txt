cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)
add_subdirectory(examples)

#include_directories(.)
#include_directories(src)

#add_executable(LittleGUI
#        examples/CMakeLists.txt
#        src/CMakeLists.txt
#        src/library.cpp
#        src/library.h
#        CMakeLists.txt examples/guiapp/main.cpp)
#