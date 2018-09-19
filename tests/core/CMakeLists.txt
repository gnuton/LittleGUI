set(APP_NAME TestCore)

find_package (Threads REQUIRED)

# Add littlegui lib
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/src")
find_package(LittleGUI REQUIRED)
include_directories("${LITTLEGUI_INCLUDE_DIRS}")

# Add littlegui lib
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third_party")
find_package(Catch REQUIRED)
include_directories("${CATCH_INCLUDE_DIRS}")

add_executable(
        ${APP_NAME}
        Main.cpp
        Signal.cpp
        LGObject.cpp
        Property.cpp Property.cpp Logger.cpp Singleton.cpp)

target_link_libraries(
        ${APP_NAME}
        ${LITTLEGUI_LIBRARIES}
        ${CATCH_LIBRARIES}
        Threads::Threads
        ~/GITonio/LittleGUI/build/third_party/catch/libcatch.a
)
