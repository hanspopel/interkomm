cmake_minimum_required (VERSION 3.0)
set(OSX TRUE)
set(IOS FALSE)

# include intercom specific cmake 
include(../interkomm.cmake)

set(TARGET_NAME ${NAME}_osx)


# set Apple development team ID
set(DEVELOPMENT_TEAM_ID ${TEAMID})  


# include osx specific cmake
#include(osx.cmake)

include(../../../../zdb/scripts/osx.cmake)


install(TARGETS "${TARGET_NAME}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../../../products/osx")

target_compile_definitions(${TARGET_NAME} PUBLIC GL_SILENCE_DEPRECATION=1)
target_compile_definitions(zdb_osx PUBLIC GL_SILENCE_DEPRECATION=1)
