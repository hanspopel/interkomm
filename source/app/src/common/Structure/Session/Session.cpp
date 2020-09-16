//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Session.h"

Session::Session(ZDB * a_zdb) : StructureBase(a_zdb) {
    init();
}

Session::Session(ZDB * a_zdb, string a_name) : StructureBase(a_zdb, a_name) {
    init();
}

void Session::init(){
    channels = new Channels;
    roles = new Roles;
}

bool Session::save_latest_session(string a_name, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
    string path = "/Sessions/latest_session.session";
    
    mss * session = new mss(0001);
    session->write_string(a_name);

    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path, session->session_content, session->write_offset);
        delete session;
    });
    
    return true;
}

bool Session::save_session(Session * a_session, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
        
    string session_name = a_session->_name();
    Session::save_latest_session(session_name,a_zdb);

    string folder_path = "/Sessions/" + session_name + "/";
    createDirectoryAtPath(folder_path);
    string path = "/Sessions/" + session_name + "/" + session_name + ".session";
    
    mss * session = new mss(0001);
    session->write_string(session_name);

    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath(path, session->session_content, session->write_offset);
        delete session;
    });
    
    return true;

}


Session * Session::load_latest_session(ZDB * a_zdb){
    
    string path = "/Sessions/latest_session.session";
    
    unsigned long length = 0;
    void * content = loadDataAtPath(path, &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        string a_session_name = session->read_string();

        path = "/Sessions/" + a_session_name + "/" + a_session_name + ".session";
        Session * current_session = Session::load_session(path, a_zdb);
        if (current_session) {
            return current_session;
        }
        delete session;
    }
    
    Session * a_session = new Session(a_zdb,"default");
    save_session(a_session, a_zdb);
    
    return a_session;
}

Session * Session::load_session(string path, ZDB * a_zdb){
            
    unsigned long length = 0;
    void * content = loadDataAtPath(path, &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        string a_session_name = session->read_string();
        Session * current_session = new Session(a_zdb, a_session_name);
        
        Role::load_roles(current_session,a_zdb);
        Channel::load_channels(current_session,a_zdb);
        
        if (current_session) {
            return current_session;
        }
        delete session;
    }
    
    return 0;
}
