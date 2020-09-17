//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Channel.h"
#include "Interkomm.h"

Channel::Channel(ZDB * a_zdb) : StructureBase(a_zdb) {
    init();
}

Channel::Channel(ZDB * a_zdb, string a_name) : StructureBase(a_zdb, a_name) {
    init();
}

Channel::Channel(ZDB * a_zdb, vector<Role*>* chanroles)  : StructureBase(a_zdb){
    init();
}

void Channel::init(){
    channel_users = new Users();
    channels_roles = new Roles();
    channels_roles->push_back(new Role(zdb, "sess"));
}


void Channel::auto_add_user(string a_name){
    bool user_found = false;
    
    for (User * a_user:*channel_users) {
        if (a_name == a_user->_name()) {
            user_found = true;
            break;
        }
    }
    if (!user_found) {
        channel_users->push_back(new User(zdb,a_name));
    }
}

void Channel::auto_add_role(string a_name){
    bool role_found = false;
    
    for (Role * a_role:*channels_roles) {
        if (a_name == a_role->_name()) {
            role_found = true;
            break;
        }
    }
    if (!role_found) {
        channels_roles->push_back(new Role(zdb,a_name));
    }
}

bool Channel::save_channel(mss * session, Channel * a_channel, ZDB * a_zdb){
    session->write_string(a_channel->_name());
    return false;
}

Channel * Channel::load_channel(mss * session, ZDB * a_zdb){
    Channel * a_channel = new Channel(a_zdb,session->read_string());
    return a_channel;
}

bool Channel::save_channels(Session * a_session, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
        
    mss * session = new mss(0001);
    string session_name = a_session->_name();
    session->write_string(session_name);
    session->write_int(static_cast<int>(a_session->_channels()->size()));
    
    for (Channel * a_channel:*a_session->_channels()) {
        save_channel(session, a_channel, a_zdb);
    }
    
    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path_for_session(a_session, Channel::get_extension()), session->session_content, session->write_offset);
        delete session;
    });
    
    return true;
}

bool Channel::load_channels(Session * a_session, ZDB * a_zdb){
    
    
    unsigned long length = 0;
    void * content = loadDataAtPath(path_for_session(a_session, Channel::get_extension()), &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        session->version = 2;
        string aname = session->read_string();
        int a_size = session->read_int();
        
        for (int i = 0; i<a_size; i++) {
            a_session->_channels()->push_back(Channel::load_channel(session, a_zdb));
        }
        
        delete session;
    }
    
    return true;
}
