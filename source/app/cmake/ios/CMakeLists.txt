
cmake_minimum_required (VERSION 3.0)

set(IOS TRUE)

include(../interkomm.cmake)


# set Apple development team ID
set(DEVELOPMENT_TEAM_ID ${TEAMID})  

# set to your app's bundle identifier                   
set(APP_BUNDLE_IDENTIFIER ${BUNDLEID})  



# include ios specific cmake
#include(ios.cmake)

include(../../../../zdb/scripts/ios.cmake)


message(STATUS "current opus path: ${PROJECT_SOURCE_DIR}/../../../../zdb/source/libs/platform/ios/")



list(APPEND CMAKE_FRAMEWORK_PATH "${PROJECT_SOURCE_DIR}/../../../../zdb/source/libs/platform/ios/")
find_library(OPUS_LIBRARY opus)
if(NOT OPUS_LIBRARY)
  message(FATAL_ERROR "OPUS_LIBRARY not asdfound")
endif()

  message(STATUS "FRAMEWORK TARGET PATH:   $<TARGET_FILE_DIR:${PROJECT_NAME}>/Frameworks/config")



set(DEVELOPMENT_TEAM_ID "834XFBML77")                       # <== Set to your team ID from Apple
                                 # <== Set To Your app's name
set(APP_BUNDLE_IDENTIFIER "com.zerodebug.soda")                # <== Set to your app's bundle identifier
set(CODESIGNIDENTITY "Apple Development: Christian Blomert (L9R462XFCA)")                    # <== Set to your preferred code sign identity, to see list:

message(STATUS TARGET NAME: ${TARGET_NAME} ${OPUS_LIBRARY})

set(OPUS_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>/Frameworks/opus.framework)
#sign 
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../../../../zdb/source/libs/platform/ios/opus.framework ${OPUS_PATH})

  #message(STATUS "OPUS TARGET PATH:   ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION}-iphoneos/intercom_ios.app/Frameworks/opus.framework

  	#CURRENT BUILD PATH: ${CMAKE_CURRENT_BINARY_DIR}/Debug-${EFFECTIVE_PLATFORM_NAME}/intercom_ios.app/Frameworks/opus.framework")
add_custom_command (TARGET ${TARGET_NAME} POST_BUILD COMMENT "Code Signing" VERBATIM COMMAND codesign --force --options runtime --deep --sign ${CODESIGNIDENTITY} ${CMAKE_CURRENT_BINARY_DIR}/$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>-iphoneos/${PROJECT_NAME}.app/Frameworks/opus.framework)



target_link_libraries(${TARGET_NAME} ${OPUS_LIBRARY})