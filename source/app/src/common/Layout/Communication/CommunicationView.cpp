//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "CommunicationView.h"


//constructor
CommunicationView::CommunicationView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views){
    
    backgroundColor = GLTBlue();
    
    overall_view = new OverallView(a_zdb, this);
    addSubview(overall_view);
    
    a_channel_view = new ChannelView(a_zdb, this);

//    int tag = 0;
//    enter_channel_view(tag);
    
    
//
//    Channels * channels = new Channels();
//
//    for (int i = 0; i<5; i++) {
//        Channel * a_channel = new Channel();
//        channels->push_back(a_channel);
//    }
//
    

    
//
//    Channel * a_channel = new Channel();
//
//    for (int i = 0; i<2; i++) {
//        User * a_user = new User("asdasdasd");
//        a_channel->channel_users->push_back(a_user);
//    }
//
//     channel_button_map = new ChannelButtonMap();
//
//
//
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
//                GLStyleButton * user_view = channel_button_map->at(key);
//                channel_button_map->erase(key);
//                user_view->should_delete = true;
//                return user_view;
//            }
//            else if (x < channels->size()) {
//                GLStyleButton * user_view = new GLStyleButton(a_zdb);
//                user_view->titleLabel->setText(to_string(channels->at(x)->_id()));
//                channel_button_map->emplace(key, user_view);
//                return user_view;
//            }
//
//        } catch (...) {
//            return (GLStyleButton*)nullptr;
//            printf("failed source track_grid ");
//        }
//        return (GLStyleButton*)nullptr;
//    };
////    addSubview(channel_scroll_view);
//
//
//    OverallView * a_channel_view = new OverallView(a_zdb, a_channel);
//    a_channel_view->setRelativeFrame(CRectMake(0, 0.2, 0.25, 0.8)); // TODO a_channel_view width must follow x and width of appropriate ChannelView talk_button
//    addSubview(a_channel_view);
    
}

void CommunicationView::enter_detail_view(Channel * channel){
    
 overall_view->animateFrame(CRectMake(-1, 0.3, 1, 0.7), 0.2,
 false, false, false, 0, 0);
 a_channel_view->animateFrame(CRectMake(0, 0.3, 1, 0.7), 0.2,
 false, false, false, 0, 0);
}

void CommunicationView::back_to_overall_view(){
        
    overall_view->animateFrame(CRectMake(0, 0.3, 1, 0.7), 0.2,
    false, false, false, 0, 0);
    a_channel_view->animateFrame(CRectMake(1, 0.3, 1, 0.7), 0.2,
    false, false, false, 0, 0);

    }

//deconstructor
CommunicationView::~CommunicationView() {
    
    delete overall_view;
    delete a_channel_view;
}


