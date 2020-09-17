//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ChannelDialog__
#define __Engine__ChannelDialog__
#include "GLView.h"

class Session;
class Channel;
class ChannelDialog : public GLView {
public:
    ChannelDialog(ZDB * a_zdb, Session * a_sesion);
    ~ChannelDialog();
    
    Channel * current_channel;
    Session * current_session;
    GLLabel * new_channel_name_label;
    string  new_channel_name = "";
};

#endif /* defined(__Engine__ChannelDialog__) */
