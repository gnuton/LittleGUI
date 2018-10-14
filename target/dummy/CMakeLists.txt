IF (TARGET_DEVICE MATCHES DUMMY)
    MESSAGE("** Configuring Build for Dummy")
    SET(TARGET_SRC_FILES
            ../target/GenericTargetConfig.h
            ../target/dummy/DummyTargetConfig.cpp
            ../target/dummy/DummyTargetConfig.h)
ENDIF()