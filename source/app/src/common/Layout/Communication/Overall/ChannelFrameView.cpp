//
//  ChannelFrameView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelFrameView.h"
#include "CommunicationView.h"



ChannelFrameView::ChannelFrameView(ZDB * a_zdb, Channel * a_channel, CommunicationView * a_com_view) : GLView(a_zdb) {
    
    channel = a_channel;

    
    com_view = a_com_view;

    
    main_grid = new GLGridView(a_zdb,CRectMake(0, 0, 1, 1));

    main_grid->setGridSize(SizeMake(1, grid_size_y));
    main_grid->spacingY = 0;
    main_grid->spacingTop = 0;
    main_grid->spacingBottom = 0;
    main_grid->spacing_top = 0;
    main_grid->spacing_bottom = 0;
//    main_grid->backgroundColor = GLTRed();
    addSubview(main_grid);


    a_frame_channel_talk_button = new FrameChannelTalkButton(a_zdb, channel);
    a_frame_return_talk_button  = new FrameReturnTalkButton(a_zdb);
    a_frame_channel_view_button = new FrameChannelViewButton(a_zdb, channel, com_view);
    a_frame_channel_view_button->addCallbackForControlEvent(new Callback([=](GLEvent *event){
        com_view->enter_channel_view(tag);
    }), GLControlEventTouchUpInside);
    
    main_grid->addSubview(a_frame_channel_talk_button, 0, 0);
    main_grid->addSubview(a_frame_return_talk_button, 0, 1);
    main_grid->addSubview(a_frame_channel_view_button, 0, 2);
    
}

ChannelFrameView::~ChannelFrameView(){
    delete main_grid;
    delete a_frame_channel_talk_button;
    delete a_frame_return_talk_button;
    delete a_frame_channel_view_button;
}
