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
#include "dbButton.h"


class ChannelView : public GLView {
public:
    ChannelView(ZDB * a_zdb, Channel * a_channel);
    ~ChannelView();

    Channel * channel;
    GLGridScrollView * user_scroll_view;
    UserViewDict * user_view_map;
    
    
    dbButton * talk_button;
};

typedef vector <ChannelView*> ChannelViews;


#endif /* defined(__Engine__ChannelView__) */
