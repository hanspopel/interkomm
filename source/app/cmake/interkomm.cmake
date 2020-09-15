cmake_minimum_required (VERSION 3.0)

set(NAME "interkomm") 


set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Release)

set(RELATIVE_PATH_TO_SOURCE "${PROJECT_SOURCE_DIR}/app")

# add the binary tree to the search path 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/studiomux_resources")

include_directories(
${RELATIVE_PATH_TO_SOURCE}/src/common/Root/
${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/
${RELATIVE_PATH_TO_SOURCE}/src/common/BaseControls/
${RELATIVE_PATH_TO_SOURCE}/src/common/Channels/
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/**
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Browser/
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/
${RELATIVE_PATH_TO_SOURCE}/src/common/Audio/
${RELATIVE_PATH_TO_SOURCE}/src/common//Structure/**
${RELATIVE_PATH_TO_SOURCE}/src/common//User/**
${RELATIVE_PATH_TO_SOURCE}/src/common/Audio/
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls




)

#include_directories(
#${RELATIVE_PATH_TO_SOURCE}/cmake/ios/libs/include
#${RELATIVE_PATH_TO_SOURCE}/cmake/ios/libs/include/silk
#${RELATIVE_PATH_TO_SOURCE}/cmake/ios/libs/include/celt
#)

set(SRC ${PROJECT_NAME}_SRC)
set(HEADERS ${PROJECT_NAME}_HEADERS)



set(RootFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Root/Interkomm.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Root/Interkomm.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Root/MainView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Root/MainView.h
  )

    set(BaseControlsFiles
  )

  set(ConnectionFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/CallbackManager.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/CallbackManager.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/Server.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/Server.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/ConnectionManager.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/ConnectionManager.h
  )

set(LayoutFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/ContentView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/ContentView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/LayoutManager.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/LayoutManager.h
  )


set(CommunicationFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/CommunicationView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/CommunicationView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/UserView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/UserView.h
    )


set(ChannelFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Channel/ChannelView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Channel/ChannelView.h
    )

set(OverallFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/OverallView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/OverallView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrameView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrameView.h
    )


set(UserFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/User/User.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/User/User.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/User/SuperUser.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/User/SuperUser.h
  )



set(StructureFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Role.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Role.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Channel.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common//Structure/Channel.h
  )
    set(SettingsFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/NetworkSettingsView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/NetworkSettingsView.h
  )

    set(AudioFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Audio/Mixer.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Audio/Mixer.h
  )

   set(TopBarFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/TopBar.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/TopBar.h
  )

  set(TopBarControlFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/TopBarButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/TopBarButton.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/ConnectionView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/ConnectionView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/ServerView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/TopBar/Controls/ServerView.h
  )




source_group("All" FILES ${SOURCE_FILES})
source_group("Root" FILES ${RootFiles})
source_group("BaseControls" FILES ${BaseControlsFiles})
source_group("Audio" FILES ${AudioFiles})
source_group("Connection" FILES ${ConnectionFiles})

source_group("Layout" FILES ${LayoutFiles})

source_group("Layout\\Settings" FILES ${SettingsFiles})

source_group("Layout\\TopBar" FILES ${TopBarFiles})
source_group("Layout\\TopBar\\Controls" FILES ${TopBarControlFiles})

source_group("Layout\\Communication" FILES ${CommunicationFiles})
source_group("Layout\\Communication\\Overall" FILES ${OverallFiles})
source_group("Layout\\Communication\\Channel" FILES ${ChannelFiles})

source_group("User" FILES ${UserFiles})
source_group("Structure" FILES ${StructureFiles})

include_directories("${PROJECT_BINARY_DIR}")



get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

set(SRC 
    ${RELATIVE_PATH_TO_SOURCE}/src/common/main.cpp
    ${SOURCE_FILES}
    ${ChannelFiles}
    ${BaseControlsFiles}
    ${ConnectionFiles}    
    ${RootFiles}
    ${LayoutFiles}
    ${SettingsFiles}
    ${TopBarFiles}
    ${TopBarControlFiles}
    ${UserFiles}
    ${AudioFiles}
    ${StructureFiles}
    ${CommunicationFiles}
    ${ChannelFiles}
    ${OverallFiles}
 )






