//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "Mixer.h"

//constructor
Mixer::Mixer(ZDB * a_zdb, ServerManager * a_server_manager) : ALNode(a_zdb) {
    
    server_manager = a_server_manager;
    tcp_client = server_manager->client;
    
    al->use_input->setValue(true);
    
    out_buffer_float = (float*)calloc(sizeof(float), 2048);

}

//deconstructor
Mixer::~Mixer() {
    
}



void Mixer::processAudio(ALBuffer * buffer, unsigned int length) {
#ifdef __IOS__
    if (tcp_client && tcp_client->connections->size()) {
        
        float multiplier = (32768.0 * 4);
        

        v_smul(buffer->data_pointers[0], multiplier, out_buffer_float, length);
        v_smul(buffer->data_pointers[1], multiplier, out_buffer_float+length, length);
        
        tcp_client->add_channel_data(0, "fuckIt", false);
        
        if (!is_muted) {
            int out[length*2];
            memset(out, 0, sizeof(float)*2*length);
            
            v_f32i32(out_buffer_float, out, length*2);
            
            tcp_client->add_audio_stream(out, length, 2);
        }
        else {
            int out[length*2];
            memset(out, 0, length*2*sizeof(float));
            tcp_client->add_audio_stream(out, length, 2);
        }
    }
#endif
    
    
    
}
