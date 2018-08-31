cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

message(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/)
add_executable(
        GUIApp
        main.cpp)
target_link_libraries(GUIApp freaklib)

#install(TARGETS GUIApp RUNTIME DESTINATION bin)