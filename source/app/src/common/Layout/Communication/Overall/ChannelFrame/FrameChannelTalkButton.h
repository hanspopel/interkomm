//
//  ChannelFrameView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__FrameChannelTalkButton__
#define __Engine__FrameChannelTalkButton__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "Channel.h"
#include "GLButton.h"


class FrameChannelTalkButton : public GLButton {
    
public:
  
    Channel * channel;
    
    FrameChannelTalkButton(ZDB * a_zdb, Channel * a_channel);
    
    
    ~FrameChannelTalkButton();
};



#endif /* defined(__Engine__FrameChannelTalkButton__) */
