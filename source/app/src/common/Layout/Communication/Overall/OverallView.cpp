//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "OverallView.h"


//constructor
OverallView::OverallView(ZDB * a_zdb) : GLView(a_zdb) {
    
    tag = 0;
    
 //   channel_views = new ChannelViews();
    
    Channel * a_channel = new Channel(a_zdb);
    Channels * channels = new Channels();
    
    
    for (int i = 0; i<2; i++) {
        User * a_user = new User(a_zdb, "asdasdasd");
        a_channel->_users()->push_back(a_user);
    }
    
    
    for (int i = 0; i<5; i++) {
        a_channel = new Channel(a_zdb);
        channels->push_back(a_channel);
    }
    
        
    channel_button_map = new ChannelButtonMap();

//    ChannelFrameView channel_frame_view(a_zdb, a_channel);

    channel_frame_view = new ChannelFrameView(a_zdb, a_channel);
    
    
    
    addSubview(channel_frame_view);
    
//    channel_scroll_view = new GLGridScrollView(a_zdb);
//    channel_scroll_view->setRelativeFrame(CRectMake(0, 0, 1, 0.2));
//    channel_scroll_view->setGridSize(SizeMake(20, 1));
//    channel_scroll_view->setViewSize(SizeMake(4, 1));
//    channel_scroll_view->startTouchesDelayed = true;
//    channel_scroll_view->delaysContentTouchesIfNeeded = true;
//    channel_scroll_view->directionalLockEnabled = true;
//    channel_scroll_view->startTouchesIfAxisBlocked = true;
//    channel_scroll_view->clipsToBounds = true;
//    channel_scroll_view->transmitsTouchesMoved = true;
//    channel_scroll_view->isMultipleTouchEnabled = true;
//    channel_scroll_view->source_block = [=](int xx, int y, bool removing) {
//        try {
//
//            int x = xx;
//
//            string key = format("%d", x);
//
//            if (removing) {
//                dbButton * user_view = channel_button_map->at(key);
//                channel_button_map->erase(key);
//                user_view->should_delete = true;
//                return user_view;
//            }
//            else if (x < channels->size()) {
//                dbButton * user_view = new dbButton(a_zdb);
//                user_view->titleLabel->setText(to_string(channels->at(x)->_id()));
//                channel_button_map->emplace(key, user_view);
//                return user_view;
//            }
//
//        } catch (...) {
//            return (dbButton*)nullptr;
//            printf("failed source track_grid ");
//        }
//        return (dbButton*)nullptr;
//    };
//    addSubview(channel_scroll_view);
    
    
//    OverallView * a_channel_view = new OverallView(a_zdb);
//    a_channel_view->setRelativeFrame(CRectMake(0, 0.2, 0.25, 0.8)); // TODO a_channel_view width must follow x and width of appropriate ChannelView talk_button
//    addSubview(a_channel_view);
    
    
    
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
            else if (y < channel->_users()->size()) {
                UserView * user_view = new UserView(a_zdb,channel->_users()->at(y));
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
    
    
    return_button = new dbButton(a_zdb);
    return_button->setRelativeFrame(CRectMake(0, 0.8, 1, 1));
    return_button->titleLabel->setText("talk");
    addSubview(return_button);
}

//deconstructor
OverallView::~OverallView(){
    delete channel_frame_view;
}
