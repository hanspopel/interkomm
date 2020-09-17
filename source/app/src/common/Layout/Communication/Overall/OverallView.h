//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__OverallView__
#define __Engine__OverallView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "UserView.h"
#include "Channel.h"
#include "dbButton.h"
#include <vector>
#include "ChannelFrameView.h"

class CommunicationView;
typedef unordered_map <string, dbButton*> ChannelButtonMap; // TODO pro channel mind 3 buttons

class OverallView : public GLView {
    
public:
    OverallView(ZDB * a_zdb, CommunicationView * a_com_view);
    ~OverallView();

//    ChannelViews * channel_views;
    
    GLGridScrollView * channel_scroll_view;
    ChannelButtonMap * channel_button_map;
    
    ChannelFrameView * a_channel_frame_view;
    
    Channel * channel;
    GLGridScrollView * user_scroll_view;
    UserViewDict * user_view_map;
    
    ChannelFrameViews * channel_frame_views;
    CommunicationView * com_view = 0;
    
    dbButton * return_button; // directly talk back to last speaker
};


#endif /* defined(__Engine__OverallView__) */
