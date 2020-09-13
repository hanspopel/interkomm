//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__Mixer__
#define __Engine__Mixer__
#include "Engine.h"
#include "GLView.h"
#include "ALNode.h"
#include "ServerManager.h"


class Mixer : public ALNode {
public:
    Mixer(ZDB * a_zdb, ServerManager * a_server_manager);
    ~Mixer();

    ServerManager * server_manager = 0;
    TCPClient * tcp_client = 0;

    void renderAudio(ALTransport * aTransport, double aCurrentTime, ALBuffer * buffer, int length);
    
    void processAudio(ALBuffer * buffer, unsigned int length);

    float * out_buffer_float;

    
};

#endif /* defined(__Engine__Mixer__) */
