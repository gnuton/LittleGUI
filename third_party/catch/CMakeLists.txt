set(LIB_NAME catch)
project(${LIB_NAME} CXX)

add_library(
        ${LIB_NAME}
        catch.cpp
        catch.hpp)