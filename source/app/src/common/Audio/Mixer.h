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
#include "ConnectionManager.h"
#include "ALMicrophoneInput.h"


class Mixer : public ALNode {
public:
    Mixer(ZDB * a_zdb, ConnectionManager * a_connection_manager);
    ~Mixer();

    ConnectionManager * connection_manager = 0;
    TCPClient * tcp_client = 0;
    TCPServer * tcp_server = 0;

    ALMicrophoneInput * microphone_input;
    
//    void renderAudio(ALTransport * aTransport, double aCurrentTime, ALBuffer * buffer, int length);
    
    void processAudio(ALBuffer * buffer, unsigned int length);

    float * out_buffer_float;

    bool send_audio_from_microphone = true;
    bool receive_audio_from_network = true;
    
    
};

#endif /* defined(__Engine__Mixer__) */
