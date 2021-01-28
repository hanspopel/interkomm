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

// uint16_t UDPListener::PORT{UDP_PORT};


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
    
//    while(udp_listeners){
//    udp_listeners->pop_back();
//    }
//    delete udp_listeners;
    
//    delete udp_sender;
//    delete mc_udp_sender;
    

    
    delete connection_manager;
    delete main_view;
    
    
}
    

void Interkomm::init(){
    
//    a_mcgroupsend = new MCGroupSend();
    
    a_mcreceiver = new MCGroupReceive();
    a_mcreceiver->Start();

//    udp_listeners = new UDPListeners;
//
//    for( int i{0}; i < 3; i++ ) {
//    a_udp_listener = new UDPListener(zdb);
//    udp_listeners->push_back(a_udp_listener);
//    udp_listeners->back()->Start();
//    }
    
//    const boost::asio::ip::address mc_address = boost::asio::ip::make_address("239.255.0.1");
    
//    udp_server = new UDPSender(zdb);
//    mc_udp_sender = new UDPSender(mc_address, zdb);
    restore();
    
    connection_manager = new ConnectionManager(zdb, NetworkInfo::can_process_audio | NetworkInfo::forbid_loopback, "_interkomm_dns._tcp");
    
    main_view = new MainView(zdb);
    addSubview(main_view);

    mixer = new Mixer(zdb, connection_manager);
    zdb->al->output->addSource(mixer);

    connection_manager->work();
}


bool Interkomm::restore(){
    
    createDirectoryAtPath("/Sessions/");
    createDirectoryAtPath("/Settings/");
    createDirectoryAtPath("/Profile/");

    interkomm_session = Session::load_latest_session(zdb);
    interkomm_profile = Profile::load_profile(zdb);
    
    
    if (interkomm_profile->just_created) {
        interkomm_profile->just_created = false;
        
        ProfileDialog * profile_dialog = new ProfileDialog(zdb, interkomm_profile);
        profile_dialog->setIsPopupLayer(true);
        gl->addPopup(profile_dialog, true, 0.1337, GLColorWithAlpha(GLBlack(), 0.7), 0);
        
    }
    
    
    
    return false;
}
