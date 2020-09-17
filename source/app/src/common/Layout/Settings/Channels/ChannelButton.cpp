//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelButton.h"

//constructor
ChannelButton::ChannelButton(ZDB * a_zdb, Channel * a_channel) : dbButton(a_zdb) {
    
    backgroundColor = GLTRed();
    channel = a_channel;
    titleLabel->setText(a_channel->_name());
    
    
    delete_channel_button = new dbButton(a_zdb);
    addSubview(delete_channel_button);
    delete_channel_button->setRelativeFrame(CRectMake(0.7, 0, 0.3, 1));
    delete_channel_button->titleLabel->setText("X");

}

//deconstructor
ChannelButton::~ChannelButton() {
    
}

