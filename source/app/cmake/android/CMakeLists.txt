cmake_minimum_required(VERSION 3.4.1)


project(intercom)
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall")



set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_SUPPRESS_REGENERATION true)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(MAKE_APP TRUE)






set(RELATIVE_PATH_TO_SOURCE2 "${CMAKE_CURRENT_LIST_DIR}/../../")


include_directories(
${RELATIVE_PATH_TO_SOURCE2}/src/common/Root
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout
${RELATIVE_PATH_TO_SOURCE2}/src/common/Controls
${RELATIVE_PATH_TO_SOURCE2}/src/common/Connection
${RELATIVE_PATH_TO_SOURCE2}/src/common/MixerElements
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/TopBar
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/TopBar/HorizontalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/TopBar/VerticalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/HorizontalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/HorizontalMode/FaderView
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/HorizontalMode/PanView
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/HorizontalMode/GroupView
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Faders/VerticalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Settings
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Settings/HorizontalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/Settings/VerticalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/EQ
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/EQ/HorizontalMode
${RELATIVE_PATH_TO_SOURCE2}/src/common/Layout/EQ/VerticalMode
)

file(STRINGS ${RELATIVE_PATH_TO_SOURCE2}/../../build_number.txt REV_NUMBER)

set(BUILD_NUMBER ${REV_NUMBER})
set(VERSION "11.${REV_NUMBER}")


MESSAGE(STATUS 
	"



#######      CONFIGURING BUILD_VERSION.H
#######      BUILD_NUMBER: ${BUILD_NUMBER}
#######      VERSION: ${VERSION}
")

configure_file(
  ${RELATIVE_PATH_TO_SOURCE2}/../scripts/build_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/build_version.h
  @ONLY)





set(ANDROID TRUE)


add_subdirectory(../../../../zdb/source ${RELATIVE_PATH_TO_SOURCE2}/../../build/android/zdb)


#include_directories("${PROJECT_BINARY_DIR}/")

include(../intercom.cmake)



# add resources

set(RESOURCES_SRC "")
set(RESOURCES_HEADERS "")
set(RESOURCES "")

#make name unique
#set(NAME ${NAME})

if(WIN32)
include(../../../../zdb/scripts/resource_macro.txt)
ADD_RESOURCES("${NAME}" "../../resources" ${RESOURCES})

else()
include(../../../../zdb/scripts/resource_macro_zip.txt)
ADD_RESOURCES_ZIP("${NAME}" "../../resources" ${RESOURCES})

endif()

FILE(GLOB_RECURSE source_files
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_resources/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_resources/*.h
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_resources/*.c
)
source_group("${NAME}_resources" FILES ${source_files})




# add sources from app.cmake
set(BLOB ${SRC} ${RESOURCES} ${RESOURCES_SRC} ${RESOURCES_HEADERS})








add_library(intercom SHARED ${BLOB})

target_include_directories(zdb_android PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)

target_include_directories(intercom PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)


include_directories(${INCLUDE_DIRS_ZDB} ${INCLUDE_DIRS_ZDB_ANDROID})

# add lib dependencies
target_link_libraries(intercom
    zdb_android
    )












