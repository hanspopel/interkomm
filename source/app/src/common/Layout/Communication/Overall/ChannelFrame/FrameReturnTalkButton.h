//
//  ChannelFrameView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__FrameReturnTalkButton__
#define __Engine__FrameReturnTalkButton__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "Channel.h"
#include "GLButton.h"
#include "User.h"


class FrameReturnTalkButton : public GLButton{
public:
    
    User * user;
    
    FrameReturnTalkButton(ZDB * a_zdb);
    ~FrameReturnTalkButton();
    
};



#endif /* defined(__Engine__FrameReturnTalkButton__) */
