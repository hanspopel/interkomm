//
//  ChannelFrameView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelFrameView__
#define __Engine__ChannelFrameView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "Channel.h"
#include "dbButton.h"


class ChannelFrameView : public GLView {
    
public:
  
    int grid_size_y = 3;
    
    Channel * channel;
    
    ChannelFrameView(ZDB * a_zdb, Channel * a_channel);
    ~ChannelFrameView();
    
    
    GLGridView * main_grid;
    
    
    
};



#endif /* defined(__Engine__ChannelFrameView__) */
