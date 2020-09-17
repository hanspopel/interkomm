//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelsView__
#define __Engine__ChannelsView__
#include "Engine.h"
#include "ContentView.h"
#include "GLView.h"
#include "Channel.h"
#include "GLGridScrollView.h"
#include "ChannelButton.h"

typedef unordered_map <string, ChannelButton*> ChannelSetButtonMap;

class SettingsView;
class ChannelsView : public GLView {
public:
    ChannelsView(ZDB * a_zdb, Channels * a_channels, SettingsView * a_settings_view);
    ~ChannelsView();
    
    SettingsView * settings_view;
    
    ChannelSetButtonMap * channel_button_map;
    
    GLGridScrollView * channels_scroll_view;
    
    void add_channel();
    void delete_channel(Channel * a_channel);
    
    Channels * current_channels;
    

};

#endif /* defined(__Engine__ChannelsView__) */
