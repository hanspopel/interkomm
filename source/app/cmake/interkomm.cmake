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
${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/**
${RELATIVE_PATH_TO_SOURCE}/src/common/Audio/
${RELATIVE_PATH_TO_SOURCE}/src/common//Structure/**
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
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/MonitorThread.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Connection/MonitorThread.h
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

set(DialogFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Dialog/ProfileDialog.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Dialog/ProfileDialog.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Dialog/ChannelDialog.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Dialog/ChannelDialog.h
)

set(ChannelViewFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Channel/ChannelView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Channel/ChannelView.h
    )

set(OverallFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/OverallView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/OverallView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrameView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrameView.h
    )

set(ChannelFrameFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameChannelTalkButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameChannelTalkButton.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameReturnTalkButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameReturnTalkButton.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameChannelViewButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Communication/Overall/ChannelFrame/FrameChannelViewButton.h
    )



set(UserFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/User.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/User.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/Profile.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/Profile.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/SuperUser.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/User/SuperUser.h
  )


set(StructureFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/StructureBase.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/StructureBase.h
  )

set(RoleFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Role/Role.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Role/Role.h

  )


  set(ChannelFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Channel/Channel.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Channel/Channel.h
  )

    set(SessionFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Session/Session.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Session/Session.h
  )

      set(WorkspaceFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Workspace/Workspace.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Structure/Workspace/Workspace.h
  )


  set(SettingsFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsView.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsDetailBase.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/SettingsDetailBase.h
  )

  set(RoleSettingsFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Roles/RoleButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Roles/RoleButton.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Roles/RolesView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Roles/RolesView.h
  )

  set(ChannelSettingsFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Channels/ChannelButton.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Channels/ChannelButton.h
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Channels/ChannelsView.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Channels/ChannelsView.h
  )

  set(ProfileSettingsFiles
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Profile/ProfilePage.cpp
    ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Settings/Profile/ProfilePage.h
  )


  # set(DebugFiles
  #   ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Debug/DebugView.cpp
  #   ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Debug/DebugView.h
  #   ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Debug/NetworkDebugView.cpp
  #   ${RELATIVE_PATH_TO_SOURCE}/src/common/Layout/Debug/NetworkDebugView.h
  # )

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


include(${RELATIVE_PATH_TO_SOURCE}/../zbd/source/cmake/includes/zdb_server.cmake)

source_group("ZDB\\ServerBase" FILES ${gZDBServerCommon})

source_group("All" FILES ${SOURCE_FILES})
source_group("Root" FILES ${RootFiles})
source_group("BaseControls" FILES ${BaseControlsFiles})
source_group("Audio" FILES ${AudioFiles})
source_group("Connection" FILES ${ConnectionFiles})

source_group("Layout" FILES ${LayoutFiles})

source_group("Layout\\Settings" FILES ${SettingsFiles})
source_group("Layout\\Settings\\Channels" FILES ${ChannelSettingsFiles})
source_group("Layout\\Settings\\Roles" FILES ${RoleSettingsFiles})
source_group("Layout\\Settings\\Profile" FILES ${ProfileSettingsFiles})



source_group("Layout\\TopBar" FILES ${TopBarFiles})
source_group("Layout\\Debug" FILES ${DebugFiles})
source_group("Layout\\Dialog" FILES ${DialogFiles})
source_group("Layout\\TopBar\\Controls" FILES ${TopBarControlFiles})

source_group("Layout\\Communication" FILES ${CommunicationFiles})
source_group("Layout\\Communication\\Overall" FILES ${OverallFiles})
source_group("Layout\\Communication\\Overall\\ChannelFrame" FILES ${ChannelFrameFiles})
source_group("Layout\\Communication\\Channel" FILES ${ChannelFiles})
source_group("Layout\\Communication\\Channel" FILES ${ChannelViewFiles})

source_group("User" FILES ${UserFiles})
source_group("Structure" FILES ${StructureFiles})
source_group("Structure\\User" FILES ${UserFiles})
source_group("Structure\\Session" FILES ${SessionFiles})
source_group("Structure\\Role" FILES ${RoleFiles})
source_group("Structure\\Workspace" FILES ${WorkspaceFiles})
source_group("Structure\\Channel" FILES ${ChannelFiles})

include_directories("${PROJECT_BINARY_DIR}")



get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

set(SRC 
    ${RELATIVE_PATH_TO_SOURCE}/src/common/main.cpp
    ${SOURCE_FILES}
    ${gZDBServerCommon}
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
    ${ChannelViewFiles}
    ${OverallFiles}
    ${ChannelFrameFiles}
    ${ProfileFiles}
    ${DebugFiles}
    ${RoleSettingsFiles}
    ${ChannelSettingsFiles}
    ${RoleFiles}
    ${ChannelFiles}
    ${SessionFiles}
    ${WorkspaceFiles}
    ${DialogFiles}
    ${ProfileSettingsFiles}
 )






