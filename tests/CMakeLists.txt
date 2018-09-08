project(UnitTests CXX)

set(CATCH_H ../third_party/catch2/catch.hpp)


set(FILES
        test.cpp
        test2.cpp
        ${CATCH_H})

add_executable(Test1 ${FILES})
