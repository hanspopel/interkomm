cmake_minimum_required (VERSION 3.0)
set(WIN32 TRUE)
set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0)

add_subdirectory(../../../zdb/source ../build/zdb)
include(../touchable.cmake)

#disable zero_check
set(CMAKE_SUPPRESS_REGENERATION true)
# add the executable
add_executable (${NAME} ${BLOB})

set_property(TARGET ${NAME} PROPERTY VS_WINRT_COMPONENT TRUE)

add_dependencies(${NAME} zdb_win)
#add_dependencies(${NAME} install)


if(MSVC_VERSION GREATER 1700)
  set(COMPILER_VERSION "12")
elseif(MSVC_VERSION GREATER 1600)
  set(COMPILER_VERSION "11")
endif()

set (APP_MANIFEST_NAME Package.appxmanifest)


target_compile_definitions(${NAME} PRIVATE WIN32=1 WIN64=1 _LIB=1 WINSTORE=1 HAS_TIMESPEC=1)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
  set(PLATFORM STORE)
else()
  set(PLATFORM DESKTOP)
  message(FATAL_ERROR "This app supports Store / Phone only. Please edit the target platform.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	target_link_libraries(${NAME} mincore.lib mfuuid.lib kernel32.lib user32.lib)

	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/audio")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/base")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/midi")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/graphics")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/graphics/freetypegl")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/osc")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/common/resources")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/png")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/portaudio")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/Accelerate")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/ffts")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/libs/platform/uwp/libdispatch")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/non-apple/ffts")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/non-apple/png")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/non-apple/Accelerate")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/portaudio")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp/freetype")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/uwp")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/non-apple")
	include_directories("${PROJECT_SOURCE_DIR}/../../../zdb/source/src/platform/non-ios")

	link_directories("C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/lib")
add_definitions(/W1)

configure_file(
	Package_vc${COMPILER_VERSION}.${PLATFORM}.appxmanifest.in
    ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
    @ONLY)


# link

target_link_libraries(${NAME} zdb_win)
set_target_properties(${NAME} PROPERTIES COMPILE_FLAGS "-DUSE_ZDB_WIN")

    #<AppContainerApplication>true</AppContainerApplication>
    #<ApplicationType>Windows Store</ApplicationType>
    #<WindowsTargetPlatformVersion Condition=" '$(WindowsTargetPlatformVersion)' == '' ">10.0.16299.0</WindowsTargetPlatformVersion>
    #<WindowsTargetPlatformMinVersion>10.0.10586.0</WindowsTargetPlatformMinVersion>
    #<ApplicationTypeRevision>10.0</ApplicationTypeRevision>


#cmake ../source/cmake/uwp -G"Visual Studio 15 2017" -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0
#if libdispatch throws errors about dllimport.. set target level to 10.0.10586.0
#copy libGLESv2.dll & libEGL.dll - make touchAble startup project