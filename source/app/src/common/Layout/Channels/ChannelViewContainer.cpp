//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelViewContainer.h"


//constructor
ChannelViewContainer::ChannelViewContainer(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views) {
    
    channel_views = new ChannelViews();
    Channels * channels = new Channels();
    
    for (int i = 0; i<20; i++) {
        Channel * a_channel = new Channel();
        channels->push_back(a_channel);
    }
    
    
    
    
    Channel * a_channel = new Channel();
    
    for (int i = 0; i<20; i++) {
        User * a_user = new User("asdasdasd");
        a_channel->channel_users->push_back(a_user);
    }
    
     channel_button_map = new ChannelButtonMap();


    
    channel_scroll_view = new GLGridScrollView(a_zdb);
    channel_scroll_view->setRelativeFrame(CRectMake(0, 0, 1, 0.2));
    channel_scroll_view->setGridSize(SizeMake(20, 4));
    channel_scroll_view->setViewSize(SizeMake(4, 1));
    channel_scroll_view->startTouchesDelayed = true;
    channel_scroll_view->delaysContentTouchesIfNeeded = true;
    channel_scroll_view->directionalLockEnabled = true;
    channel_scroll_view->startTouchesIfAxisBlocked = true;
    channel_scroll_view->clipsToBounds = true;
    channel_scroll_view->transmitsTouchesMoved = true;
    channel_scroll_view->isMultipleTouchEnabled = true;
    channel_scroll_view->source_block = [=](int xx, int y, bool removing) {
        try {
            
            int x = xx;
            
            string key = format("%d", x);
            
            if (removing) {
                dbButton * user_view = channel_button_map->at(key);
                channel_button_map->erase(key);
                user_view->should_delete = true;
                return user_view;
            }
            else if (x < channels->size()) {
                dbButton * user_view = new dbButton(a_zdb);
                user_view->titleLabel->setText(to_string(channels->at(x)->_id()));
                channel_button_map->emplace(key, user_view);
                return user_view;
            }
            
        } catch (...) {
            return (dbButton*)nullptr;
            printf("failed source track_grid ");
        }
        return (dbButton*)nullptr;
    };
    addSubview(channel_scroll_view);
    
    
    ChannelView * a_channel_view = new ChannelView(a_zdb, a_channel);
    a_channel_view->setRelativeFrame(CRectMake(0, 0.2, 1, 0.8));
    addSubview(a_channel_view);
    
}

//deconstructor
ChannelViewContainer::~ChannelViewContainer() {
    
}

