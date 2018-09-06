set(CMAKE_CXX_STANDARD 14)
set(LIB_NAME freaklib)
message("** Configuring ${LIB_NAME}")

add_library(
        ${LIB_NAME}
        library.cpp
        library.h)

target_link_libraries(
        ${LIB_NAME}
        ${TARGET_EXTERNAL_LIBS})
