SET(CMAKE_CXX_STANDARD 14)
SET(LIB_NAME littlegui)
MESSAGE("** Configuring ${LIB_NAME}")

ADD_LIBRARY(
        ${LIB_NAME}
        core/Macros.h
        core/Signal.h
        core/Property.h
        library.cpp
        library.h
        core/LGObject.cpp
        core/LGObject.h core/Mutex.h core/Logger.cpp core/Logger.h core/Singleton.h)

TARGET_LINK_LIBRARIES(
        ${LIB_NAME}
        ${TARGET_EXTERNAL_LIBS})

#configure_file(configure.h.in filename.h)
