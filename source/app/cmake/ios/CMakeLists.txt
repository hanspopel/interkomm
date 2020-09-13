
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


target_link_libraries(${NAME}_ios ${PROJECT_SOURCE_DIR}/libs/libopus.a)