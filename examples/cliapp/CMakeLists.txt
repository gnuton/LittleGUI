cmake_minimum_required(VERSION 3.12)

include_directories(${CMAKE_SOURCE_DIR}/src/)
set(APP_NAME CLIApp)
message("** Configuring ${APP_NAME}")

add_executable(
        ${APP_NAME}
        main.cpp)

target_link_libraries(
        ${APP_NAME}
        ${TARGET_EXTERNAL_LIBS}
        freaklib)