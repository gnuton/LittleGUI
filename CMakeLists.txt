CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

# Options
set(TARGET_DEVICE "DUMMY" CACHE STRING "Sets the device target")

INCLUDE("functions.cmake")
SET(CMAKE_CXX_STANDARD 14)

# Load hardware target profiles
SET(TARGET_EXTERNAL_LIBS)
LOAD_CMAKEFILES_IN_DIR("target")
PROJECT(LittleGUI)

# Build code in these dirs
ADD_SUBDIRECTORY(third_party)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(tests)
