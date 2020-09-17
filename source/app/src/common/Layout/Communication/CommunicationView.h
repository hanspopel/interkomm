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
    
    OverallView * overall_view;
    ChannelView * a_channel_view;

    CommunicationView(ZDB * a_zdb, GLViews * content_views);
    
//    void enter_channel_view(int tag);
    void back_to_overall_view();
    
    ~CommunicationView();
    
//    GLViews * content_views;
    void enter_detail_view(Channel * channel);
    
//    ChannelViews * channel_views;
//
//    GLGridScrollView * channel_scroll_view;
//    ChannelButtonMap * channel_button_map;
//
};



#endif /* defined(__Engine__CommunicationView__) */
