//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelViewContainer__
#define __Engine__ChannelViewContainer__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "ChannelView.h"


typedef unordered_map <string, dbButton*> ChannelButtonMap;

class ChannelViewContainer : public ContentView {
public:
    ChannelViewContainer(ZDB * a_zdb, GLViews * content_views);
    ~ChannelViewContainer();
    
    ChannelViews * channel_views;
    
    GLGridScrollView * channel_scroll_view;
    ChannelButtonMap * channel_button_map;
    
};

#endif /* defined(__Engine__ChannelViewContainer__) */
