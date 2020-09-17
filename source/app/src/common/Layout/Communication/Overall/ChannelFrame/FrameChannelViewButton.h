//
//  ChannelFrameView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__FrameChannelViewButton__
#define __Engine__FrameChannelViewButton__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "Channel.h"
#include "GLButton.h"

class CommunicationView;
class FrameChannelViewButton : public GLButton {
    
public:
      
    Channel * channel;
    CommunicationView * com_view;
    
    FrameChannelViewButton(ZDB * a_zdb, Channel * a_channel, CommunicationView * a_com_view);
    ~FrameChannelViewButton();
};



#endif /* defined(__Engine__FrameChannelViewButton__) */
