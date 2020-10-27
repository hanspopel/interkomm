//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelView__
#define __Engine__ChannelView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "UserView.h"
#include "Channel.h"
#include "GLStyleButton.h"

class CommunicationView;
class ChannelView : public GLView {
public:
    ChannelView(ZDB * a_zdb, CommunicationView * a_com_view);
    ~ChannelView();

    Channel * channel;
    GLGridScrollView * user_scroll_view;
    UserViewDict * user_view_map;
    
    CommunicationView * com_view = 0;

    
    GLStyleButton * talk_button;
};

#endif /* defined(__Engine__ChannelView__) */
