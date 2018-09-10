SET(CMAKE_CXX_STANDARD 14)
SET(LIB_NAME littlegui)
MESSAGE("** Configuring ${LIB_NAME}")

ADD_LIBRARY(
        ${LIB_NAME}
        library.cpp
        library.h)

TARGET_LINK_LIBRARIES(
        ${LIB_NAME}
        ${TARGET_EXTERNAL_LIBS})

#configure_file(configure.h.in filename.h)
