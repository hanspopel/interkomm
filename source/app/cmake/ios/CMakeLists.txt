
cmake_minimum_required (VERSION 3.0)

#project(studiomux)
set(IOS TRUE)

include(../studiomux.cmake)


# set Apple development team ID
set(DEVELOPMENT_TEAM_ID ${TEAMID})  

# set to your app's bundle identifier                   
set(APP_BUNDLE_IDENTIFIER ${BUNDLEID})  



# include ios specific cmake
#include(ios.cmake)

include(../../../../zdb/scripts/ios.cmake)


