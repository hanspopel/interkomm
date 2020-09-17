//
//  ChannelFrameView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "FrameReturnTalkButton.h"



FrameReturnTalkButton::FrameReturnTalkButton(ZDB * a_zdb) : GLButton(a_zdb) {
    
    titleLabel->setText("User Return");
    highlightsWhenTouched = true;

    backgroundColor = GLTGreen();
    relativeImageFrame = GLFullRect();
    
}

FrameReturnTalkButton::~FrameReturnTalkButton(){

}
