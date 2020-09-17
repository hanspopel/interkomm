//
//  ChannelFrameView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "FrameChannelViewButton.h"



FrameChannelViewButton::FrameChannelViewButton(ZDB * a_zdb, Channel * a_channel, CommunicationView * a_com_view) : GLButton(a_zdb) {
    
    channel = a_channel;
    
    // a_communication_view->enter_channel_view(tag);
    
    titleLabel->setText("Select ChannelView");
    highlightsWhenTouched = true;

    backgroundColor = GLTOrange();
    relativeImageFrame = GLFullRect();

    addCallbackForControlEvent(new Callback([=](GLEvent * event){
        setValue(!value);
        if (tag > -1) {
      
            
            
        }
    }), GLControlEventTouchUpInside);

    
    
}



FrameChannelViewButton::~FrameChannelViewButton(){

}
