cmake_minimum_required(VERSION 3.12)

include_directories(${CMAKE_SOURCE_DIR}/src/)
set(APP_NAME GUIApp)
message("** Configuring ${APP_NAME}")

add_executable(
        ${APP_NAME}
        main.cpp)

target_link_libraries(
        ${APP_NAME}
        ${TARGET_EXTERNAL_LIBS}
        freaklib)

list(INSERT VPK_BUNDLED_FILES
        FILE sce_sys/icon0.png sce_sys/icon0.png
        FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
        FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
        FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

        FILE assets/fonts/segoeui.ttf resources/fonts/segoeui.ttf
        )

BUILD_VPK(APP_VERSION VPK_BUNDLED_FILES)