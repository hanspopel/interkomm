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


class ChannelView : public ContentView {
public:
    ChannelView(ZDB * a_zdb, GLViews * content_views);
    ~ChannelView();

    GLGridScrollView * user_scroll_view;
    
    UserViewDict * user_views;
    
    
  
    void touchesMoved(GLTouch * touch);
    void touchesBegan(GLTouch * touch);

    float initial_touch_x = 0;
    
};

#endif /* defined(__Engine__AudiomuxView__) */
