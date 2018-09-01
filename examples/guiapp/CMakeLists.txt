cmake_minimum_required(VERSION 3.12)

include_directories(${CMAKE_SOURCE_DIR}/src/)
add_executable(
        GUIApp
        main.cpp)
target_link_libraries(GUIApp freaklib)