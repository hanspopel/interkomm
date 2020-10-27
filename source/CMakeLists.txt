

cmake_minimum_required (VERSION 3.0)

if (WIN32) 
set (CMAKE_SYSTEM_VERSION 10.0 CACHE STRING INTERNAL FORCE)
add_definitions(-DWIN32)
endif(WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

SET(INHERITED_STRING "\$")
string(APPEND INHERITED_STRING "{inherited}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_LINK_FLAGS ${INHERITED_STRING})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${INHERITED_STRING}")


project("interkomm_all")

#SET(DEPLOY FALSE CACHE BOOL "Deployment Mode Enabled" FORCE)
#SET(TEAMID "834XFBML77" CACHE STRING "Apple Codesign Team ID" FORCE)
#SET(BUNDLEID "com.zerodebug.code" CACHE STRING "Apple iOS Bundle Identifier" FORCE)

option(DEPLOY "Deployment Mode" OFF)
option(TEAMID "Apple Codesign Team ID" 834XFBML77)
option(BUNDLEID "Apple iOS Bundle Identifier" com.zerodebug.studiomux)
option(VERSION_NUMBER "Version Number" 21)
option(BUILD_NUMBER "Build Number" 0)
option(VERSION "Version Name" 0.0.21)

MESSAGE(STATUS 
	"

#######      CONFIGURING BUILD_VERSION.H
#######      BUILD_NUMBER: ${BUILD_NUMBER}
#######      VERSION: ${VERSION}

")

configure_file(
  ./scripts/build_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/build_version.h
  @ONLY)




MESSAGE(STATUS 
	"

#######      DEPLOY = ${DEPLOY}
#######      TEAMID = ${TEAMID}
#######      BUNDLEID = ${BUNDLEID}

")

# disable cmake targets
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_SUPPRESS_REGENERATION true)


if (APPLE)

add_subdirectory(../zdb/source ../../build/osx/zdb/)


# add zdb for iOS:
set(OSX FALSE)
set(IOS TRUE)
set(WIN FALSE)
add_subdirectory(../zdb/source ../../build/ios/zdb)


# add application for iOS:
add_subdirectory(./app/cmake/ios ../../build/ios/app/)


# add application for OSX:
add_subdirectory(./app/cmake/osx ../../build/osx/app/)


endif(APPLE)





