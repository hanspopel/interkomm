//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "Mixer.h"

//constructor
Mixer::Mixer(ZDB * a_zdb, ConnectionManager * a_connection_manager) : ALNode(a_zdb) {
    
    connection_manager = a_connection_manager;
    tcp_client = connection_manager->tcp_client;
    tcp_server = connection_manager->server;


    out_buffer_float = (float*)calloc(sizeof(float), 2048);
    

    microphone_input = new ALMicrophoneInput(a_zdb);
    
    zdb->al->input->addSource(microphone_input);
}

//deconstructor
Mixer::~Mixer() {
    
}



void Mixer::processAudio(ALBuffer * buffer, unsigned int length) {
    

    
    if (send_audio_from_microphone) {
        for (int i = 0; i < length; i++) {
            buffer->data_pointers[0][i] = microphone_input->source_buffer->audio_data[0][i];
            buffer->data_pointers[1][i] = microphone_input->source_buffer->audio_data[0][i];
        }
        
        #ifdef __IOS__
            if (tcp_server && tcp_server->connections->size()) {
                tcp_server->start_stream();
                float multiplier = (32768.0 * 4);
                

                v_smul(buffer->data_pointers[0], multiplier, out_buffer_float, length);
                v_smul(buffer->data_pointers[1], multiplier, out_buffer_float+length, length);
                
                tcp_server->add_channel_data(0, "fuckIt", false);
                
                if (!is_muted) {
                    int out[length*2];
                    memset(out, 0, sizeof(float)*2*length);
                    
                    v_f32i32(out_buffer_float, out, length*2);
                    
                    tcp_server->add_audio_stream(out, length, 2);
                }
                else {
                    int out[length*2];
                    memset(out, 0, length*2*sizeof(float));
                    tcp_server->add_audio_stream(out, length, 2);
                }
                tcp_server->end_stream();
            }
        #endif
        
        
        
    }
    

    memset(tcp_client->left_in_buffer, 0, sizeof(float) * 1024);
    memset(tcp_client->right_in_buffer, 0, sizeof(float) * 1024);

    int num_samples = tcp_client->pull_audio_data(tcp_client->left_in_buffer, tcp_client->right_in_buffer, length, 0);
    
    for (int i = 0; i < length; i++) {
        buffer->data_pointers[0][i] = tcp_client->left_in_buffer[i];
        buffer->data_pointers[1][i] = tcp_client->right_in_buffer[i];
    }
    
}
