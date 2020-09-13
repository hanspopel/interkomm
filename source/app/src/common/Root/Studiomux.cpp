//
//  tALayoutManager.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "Studiomux.h"
#include "ZDBConsole.h"

static Studiomux * studiomux = 0;
Studiomux* Studiomux::m_pInstance = NULL;
Studiomux* Studiomux::Kit(ZDB * a_zdb)
{
    if (!m_pInstance && a_zdb)   {
        m_pInstance = new Studiomux(a_zdb);
        studiomux = m_pInstance;
        m_pInstance->init();
    }// Only allow one instance of class to be generated. *not threadsafe, only use from main during init*
    return m_pInstance;
}


//constructor
Studiomux::Studiomux(ZDB * a_zdb) : GLControl(a_zdb) {
    
}

//deconstructor
Studiomux::~Studiomux() {
    
    delete server_manager;
    delete main_view;
    delete load_save_lock;
    
}

void Studiomux::init(){
    
    load_save_lock = new CThreadMutex;
    
    createDirectoryAtPath("/Sessions/");
    
    borderColor = GLBlack();
    borderColorHighlight = GLBlack();
    borderColorOn = GLBlack();
    
    gl->set_alert_desing_for_app("MyMon");
    

    
    
    connected_to_server = addParameter("Connected To Server", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){
        
    }));


    
    zdb->gl->block_notch->setValue(true);
    zdb->gl->block_round_corner_edges->setValue(true);
    
    server_manager = new ServerManager(zdb,"_studiomux_device._tcp");

    callback_manager = server_manager->tcp_client->cb_manager;
    server_manager->tcp_client->device_id = get_uuid();


    main_view = new MainView(zdb);
    addSubview(main_view);
    
    
    
    
    gl->addTimerWithInterval(10, -1, [=]{
        save_session();
    });
    
    load("prefs.mmp");
    


}

void Studiomux::setFrame(CRect aFrame){
    GLControl::setFrame(aFrame);
}


void Studiomux::save_session() {
    if (connected_to_server->ivalue()) {

        save("prefs.mmp");
    }
}





void Studiomux::save(string path) {
    load_save_lock->Lock();
    mss * binary = new mss(0);
    binary->write_string(server_manager->last_active_server->string_value);
    binary->write_to_path(path);
    load_save_lock->Unlock();
    delete binary;
}

bool Studiomux::load(string path ) {
    
    load_save_lock->Lock();
    
    mss * binary = 0;
    //print("loading: %s", path.c_str());
    
    try {
        if (itemExistsAtPath(path)) {
            binary = new mss(path);
            if (!binary) {
                load_save_lock->Unlock();
                return false;
            }
            string last_active = binary->read_string();
            server_manager->last_active_server->setString(last_active);
            
            delete binary;
        }
    } catch (...) {
        if (binary) {
            delete binary;
        }
    }
    
    load_save_lock->Unlock();
    return false;
}
