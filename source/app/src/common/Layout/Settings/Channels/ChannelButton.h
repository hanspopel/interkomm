//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelButton__
#define __Engine__ChannelButton__
#include "Engine.h"
#include "ContentView.h"
#include "GLStyleButton.h"
#include "Channel.h"


class ChannelButton : public GLStyleButton {
public:
    ChannelButton(ZDB * a_zdb, Channel * a_channel);
    ~ChannelButton();
            
    GLStyleButton * delete_channel_button;
    
    Channel * channel = 0;
};

#endif /* defined(__Engine__ChannelButton__) */
