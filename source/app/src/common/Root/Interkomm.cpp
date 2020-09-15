//
//  tALayoutManager.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "Interkomm.h"
#include "ZDBConsole.h"
#include "ALSource.h"

static Interkomm * interkomm = 0;
Interkomm* Interkomm::m_pInstance = NULL;
Interkomm* Interkomm::Kit(ZDB * a_zdb)
{
    if (!m_pInstance && a_zdb)   {
        m_pInstance = new Interkomm(a_zdb);
        interkomm = m_pInstance;
        m_pInstance->init();
    }// Only allow one instance of class to be generated. *not threadsafe, only use from main during init*
    return m_pInstance;
}


//constructor
Interkomm::Interkomm(ZDB * a_zdb) : GLControl(a_zdb) {
    
}

//deconstructor
Interkomm::~Interkomm() {
    
    delete connection_manager;
    delete main_view;
    delete load_save_lock;
    
}

void Interkomm::init(){
    
    al->use_input->setValue(true);

    
    load_save_lock = new CThreadMutex;
    
    createDirectoryAtPath("/Sessions/");
    
    borderColor = GLBlack();
    borderColorHighlight = GLBlack();
    borderColorOn = GLBlack();
    
    gl->set_alert_desing_for_app("MyMon");
    

    
    
    connected_to_server = addParameter("Connected To Server", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){
        
    }));

    connection_manager = new ConnectionManager(zdb, NetworkInfo::can_process_audio | NetworkInfo::forbid_loopback, "_interkomm_dns._tcp");


    
    zdb->gl->block_notch->setValue(true);
    zdb->gl->block_round_corner_edges->setValue(true);
    


    main_view = new MainView(zdb);
    addSubview(main_view);
    
    
    
    
    gl->addTimerWithInterval(10, -1, [=]{
        save_session();
    });
    
    load("prefs.mmp");
    
    mixer = new Mixer(zdb, connection_manager);
    
    al->use_input->setValue(true);
    zdb->al->output->addSource(mixer);


}

void Interkomm::setFrame(CRect aFrame){
    GLControl::setFrame(aFrame);
}


void Interkomm::save_session() {
    if (connected_to_server->ivalue()) {
        save("prefs.mmp");
    }
}





void Interkomm::save(string path) {
    load_save_lock->Lock();
    mss * binary = new mss(0);
    binary->write_string("asd");
    binary->write_to_path(path);
    load_save_lock->Unlock();
    delete binary;
}

bool Interkomm::load(string path ) {
    
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
