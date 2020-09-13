cmake_minimum_required (VERSION 3.0)
set(OSX FALSE)
set(IOS FALSE)
set(RPI TRUE)

# include rpi specific cmake 
include(../intercom.cmake)

set(TARGET_NAME ${NAME}_rpi)


# set Apple development team ID
set(DEVELOPMENT_TEAM_ID ${TEAMID})  


# include osx specific cmake
#include(osx.cmake)

include(../../../../zdb/scripts/rpi.cmake)


install(TARGETS "${TARGET_NAME}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../../../products/rpi")

