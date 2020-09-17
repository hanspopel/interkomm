//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__SettingsView__ //TODO
#define __Engine__SettingsView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "OverallView.h"
#include "ChannelView.h"
#include "Role.h"
#include "Profile.h"
#include "RolesView.h"
#include "ChannelsView.h"

#define PROFILE_VIEW_TAG 2



class SettingsView : public ContentView {
public:
    SettingsView(ZDB * a_zdb, GLViews * content_views);
    ~SettingsView();
    
    Profile * current_profile;
    
    Roles * user_roles;
    Channels * current_channels;
    
    RolesView * roles_view;
    ChannelsView * channels_view;

    void load_profile(string path);
    void save_profile(string path);
    
    void setFrame(CRect aFrame);
    
    
    GLGridScrollView * settings_scroll_view;
    
    GLView * settings_overview;
    GLView * settings_detail_view;
    GLView * settings_detail_content_view;


    
    dbButtons * settings_buttons;
  
    void enter_detail_view(int tag);
    void back_to_overview();

    
    
};

#endif /* defined(__Engine__SettingsView__) */
