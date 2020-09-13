//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelView.h"


//constructor
ChannelView::ChannelView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views) {
    
    tag = 0;
    
    
    user_views = new UserViewDict;
    

    
    
    user_scroll_view = new GLGridScrollView(a_zdb);
    user_scroll_view->setGridSize(SizeMake(6, 1));
    user_scroll_view->setViewSize(SizeMake(3, 1));
    user_scroll_view->startTouchesDelayed = true;
    user_scroll_view->delaysContentTouchesIfNeeded = true;
    user_scroll_view->directionalLockEnabled = true;
    user_scroll_view->startTouchesIfAxisBlocked = true;
    user_scroll_view->transmitsTouchesMoved = true;
    user_scroll_view->isMultipleTouchEnabled = true;
    user_scroll_view->source_block = [=](int xx, int y, bool removing) {
        try {
            int x = xx;
            string key = format("%d", x);
            
            if (removing) {
                UserView * user_view = user_views->at(key);
                user_views->erase(key);
                user_view->should_delete = true;
                return user_view;
            }
            else if (x < 2) {
                UserView * user_view = new UserView(a_zdb);
                user_views->emplace(key, user_view);
                return user_view;
            }
            
        } catch (...) {
            return (UserView*)nullptr;
            printf("failed source track_grid ");
        }
        return (UserView*)nullptr;
    };
    addSubview(user_scroll_view);
    
}

//deconstructor
ChannelView::~ChannelView() {
    
}

void ChannelView::touchesBegan(GLTouch * touch){
    initial_touch_x = touch->location.x;
    ContentView::touchesBegan(touch);

}


void ChannelView::touchesMoved(GLTouch * touch){

    ContentView::touchesMoved(touch);
}


