message("** Configuring toolchain for Vita")

if (TARGET_DEVICE MATCHES VITA)
    include(vita.cmake)

    if (DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else ()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif ()

    # List of basic PS Vita external libs required by the lib
    list(INSERT
            TARGET_EXTERNAL_LIBS
            vita2d
            SceDisplay_stub # Required by: vita2d
            SceGxm_stub # Required by: vita2d
            SceCommonDialog_stub # Required by: vita2d
            SceSysmodule_stub # Required by: vita2d
            SceTouch_stub
            SceCtrl_stub
            png
            jpeg
            z # required by png for crc32
            SceNet_stub
            SceNetCtl_stub
            freetype
            ScePower_stub
            SceRegistryMgr_stub)
endif ()
