//
//  ChannelFrameView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelFrameView__
#define __Engine__ChannelFrameView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "Channel.h"
#include "User.h"

#include "FrameChannelTalkButton.h"
#include "FrameChannelViewButton.h"
#include "FrameReturnTalkButton.h"

class CommunicationView;
class ChannelFrameView : public GLView {
    
public:
  
    int grid_size_y = 3;
    
    Channel * channel;
    User * a_user;
    
    ChannelFrameView(ZDB * a_zdb, Channel * a_channel, CommunicationView * a_com_view);
    ~ChannelFrameView();
    
    CommunicationView * com_view;
    
    GLGridView * main_grid;
    
    FrameChannelTalkButton * a_frame_channel_talk_button;
    FrameReturnTalkButton * a_frame_return_talk_button;
    FrameChannelViewButton * a_frame_channel_view_button;
    
};

typedef vector <ChannelFrameView*> ChannelFrameViews;

#endif /* defined(__Engine__ChannelFrameView__) */
