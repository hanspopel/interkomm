//
//  ChannelFrameView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "FrameChannelTalkButton.h"



FrameChannelTalkButton::FrameChannelTalkButton(ZDB * a_zdb, Channel * a_channel) : GLButton(a_zdb) {
    
    channel = a_channel;

    titleLabel->setText("ChannelTalk");
    highlightsWhenTouched = true;

    backgroundColor = GLTYellow();
    relativeImageFrame = GLFullRect();

}

FrameChannelTalkButton::~FrameChannelTalkButton(){

}

