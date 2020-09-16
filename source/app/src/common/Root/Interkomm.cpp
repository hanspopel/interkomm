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
    
}

void Interkomm::init(){
    

    createDirectoryAtPath("/Sessions/");
    createDirectoryAtPath("/Settings/");

    interkomm_session = Session::load_latest_session(zdb);
    
    connection_manager = new ConnectionManager(zdb, NetworkInfo::can_process_audio | NetworkInfo::forbid_loopback, "_interkomm_dns._tcp");
    callback_manager = connection_manager->tcp_client->cb_manager;
    connection_manager->tcp_client->device_id = get_uuid();

    
    zdb->gl->block_notch->setValue(true);
    zdb->gl->block_round_corner_edges->setValue(true);


    main_view = new MainView(zdb);
    addSubview(main_view);
    
    
    mixer = new Mixer(zdb, connection_manager);
    
    al->use_input->setValue(true);
    zdb->al->output->addSource(mixer);

}
