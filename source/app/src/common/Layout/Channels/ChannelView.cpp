//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelView.h"


//constructor
ChannelView::ChannelView(ZDB * a_zdb, Channel * a_channel) : GLView(a_zdb) {
    
    tag = 0;
    
    
    user_view_map = new UserViewDict;
    
    channel = a_channel;
    
    
    user_scroll_view = new GLGridScrollView(a_zdb);
    user_scroll_view->setRelativeFrame(CRectMake(0, 0, 1, 0.8));
    user_scroll_view->setGridSize(SizeMake(1, 20));
    user_scroll_view->setViewSize(SizeMake(1, 5));
    user_scroll_view->startTouchesDelayed = true;
    user_scroll_view->delaysContentTouchesIfNeeded = true;
    user_scroll_view->directionalLockEnabled = true;
    user_scroll_view->startTouchesIfAxisBlocked = true;
    user_scroll_view->clipsToBounds = true;
    user_scroll_view->transmitsTouchesMoved = true;
    user_scroll_view->isMultipleTouchEnabled = true;
    user_scroll_view->source_block = [=](int xx, int y, bool removing) {
        try {
            string key = format("%d", y);
            
            if (removing) {
                UserView * user_view = user_view_map->at(key);
                user_view_map->erase(key);
                user_view->should_delete = true;
                return user_view;
            }
            else if (y < channel->channel_users->size()) {
                UserView * user_view = new UserView(a_zdb,channel->channel_users->at(y));
                user_view_map->emplace(key, user_view);
                return user_view;
            }
            
        } catch (...) {
            return (UserView*)nullptr;
            printf("failed source track_grid ");
        }
        return (UserView*)nullptr;
    };
    addSubview(user_scroll_view);
    
    
    talk_button = new dbButton(a_zdb);
    talk_button->setRelativeFrame(CRectMake(0, 0.8, 1, 0.2));
    talk_button->titleLabel->setText("talk");
    addSubview(talk_button);
}

//deconstructor
ChannelView::~ChannelView() {
    
}

