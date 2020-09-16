//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Channel.h"

Channel::Channel(ZDB * a_zdb) : StructureBase(a_zdb) {
    channel_users = new Users;
}

Channel::Channel(ZDB * a_zdb, string a_name) : StructureBase(a_zdb, a_name) {
    
    channel_users = new Users;
}

Channel::Channel(ZDB * a_zdb, vector<Role*>* chanroles)  : StructureBase(a_zdb){

}


void Channel::setuproles(){

}


bool Channel::save_channel(mss * session, Channel * a_channel, ZDB * a_zdb){
    session->write_string(a_channel->_name());
    return false;
}

Channel * Channel::load_channel(mss * session, ZDB * a_zdb){
    Channel * a_channel = new Channel(a_zdb,session->read_string());
    return a_channel;
}

bool Channel::save_channels(string path, Channels * a_channels, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
    
    mss * session = new mss(0001);
    string a_name = "asda";
    session->write_string(a_name);
    session->write_int(static_cast<int>(a_channels->size()));
    
    for (Channel * a_channel:*a_channels) {
        save_channel(session, a_channel, a_zdb);
    }
    
    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path, session->session_content, session->write_offset);
        delete session;
    });
    
    return true;
}
bool Channel::load_channels(string path, Channels * a_channels, ZDB * a_zdb){
    
    
    unsigned long length = 0;
    void * content = loadDataAtPath(path, &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        session->version = 2;
        string aname = session->read_string();
        int a_size = session->read_int();
        
        for (int i = 0; i<a_size; i++) {
            a_channels->push_back(Channel::load_channel(session, a_zdb));
        }
        
        delete session;
    }
    
    return true;
}
