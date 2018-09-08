SET(CMAKE_CXX_STANDARD 14)
SET(LIB_NAME freaklib)
MESSAGE("** Configuring ${LIB_NAME}")

ADD_LIBRARY(
        ${LIB_NAME}
        library.cpp
        library.h)

TARGET_LINK_LIBRARIES(
        ${LIB_NAME}
        ${TARGET_EXTERNAL_LIBS})
