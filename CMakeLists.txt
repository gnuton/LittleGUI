cmake_minimum_required(VERSION 3.12)
project(LittleGUI)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(docs)
include_directories(examples)
include_directories(src)
include_directories(target)
include_directories(tests)

add_executable(LittleGUI
        examples/cliapp/main.cpp
        examples/guiapp/main.cpp
        src/library.cpp
        src/library.h
        target/vita/CMakeLists.txt
        target/vita/vita.cmake
        tests/CMakeLists.txt
        CMakeLists.txt
        functions.cmake
        LICENSE
        README.md)
