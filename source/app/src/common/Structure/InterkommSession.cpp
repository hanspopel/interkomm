//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "InterkommSession.h"

InterkommSession::InterkommSession(ZDB * a_zdb) : ZDBObject(a_zdb) {


    
    
}

InterkommSession::InterkommSession(ZDB * a_zdb, string a_name) : ZDBObject(a_zdb) {

    name = a_name;
    
}


bool InterkommSession::save_session(mss * session, InterkommSession * a_channel, ZDB * a_zdb){
    session->write_string(a_channel->_name());
    return false;
}

InterkommSession * InterkommSession::load_session(mss * session, ZDB * a_zdb){
    InterkommSession * a_channel = new InterkommSession(a_zdb,session->read_string());
    return a_channel;
}

bool InterkommSession::save_sessions(string path, InterkommSessions * a_channels, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
    
    mss * session = new mss(0001);
    string a_name = "asda";
    session->write_string(a_name);
    session->write_int(static_cast<int>(a_channels->size()));
    
    for (InterkommSession * a_channel:*a_channels) {
        save_session(session, a_channel, a_zdb);
    }
    
    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path, session->session_content, session->write_offset);
        delete session;
    });
    
    return true;
}
bool InterkommSession::load_sessions(string path, InterkommSessions * a_channels, ZDB * a_zdb){
    
    
    unsigned long length = 0;
    void * content = loadDataAtPath(path, &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        session->version = 2;
        string aname = session->read_string();
        int a_size = session->read_int();
        
        for (int i = 0; i<a_size; i++) {
            a_channels->push_back(InterkommSession::load_session(session, a_zdb));
        }
        
        delete session;
    }
    
    return true;
}
