cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

add_library(
        freaklib
        library.cpp
        library.h)

#install(TARGETS freaklib
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib)