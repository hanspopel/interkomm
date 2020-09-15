//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__CommunicationView__ //TODO
#define __Engine__CommunicationView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "OverallView.h"
#include "ChannelView.h"

// typedef unordered_map <string, dbButton*> ChannelButtonMap;

class CommunicationView : public ContentView {
public:
    CommunicationView(ZDB * a_zdb, GLViews * content_views);
    ~CommunicationView();
    
//    GLViews * content_views;

    
    OverallView * overall_view;
    ChannelView * channel_view;
    
//    ChannelViews * channel_views;
//
//    GLGridScrollView * channel_scroll_view;
//    ChannelButtonMap * channel_button_map;
//
};



#endif /* defined(__Engine__CommunicationView__) */
