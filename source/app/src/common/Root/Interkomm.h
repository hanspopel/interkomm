//
//  MyMon.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__Interkomm__
#define __Engine__Interkomm__
#include "Engine.h"
#include "GLControl.h"
#include "MainView.h"
#include "TCPCallbackManager.h"
#include "ConnectionManager.h"
#include "ThreadMutex.h"
#include "TCPClient.h"
#include "CallbackManager.h"
#include "Server.h"
#include "Mixer.h"
#include "Session.h"
#include "Profile.h"
#include "ProfileDialog.h"

#include "MCGroups.h"
#include "MCGroupSendReceive.h"

//#include "UDPServer.h"
//#include "UDPClient.h"


class Interkomm : public GLControl  {
public:
 //   ZDB * a_zdb{0}; // for testing with UDPServer Class
    
    Interkomm(ZDB * a_zdb);
    ~Interkomm();
    
    MainView * main_view = 0;
        
    ConnectionManager * connection_manager;
    
//    UDPListener * udp_listener{0};

//    UDPSender * udp_sender{0};
    
//    UDPSender * mc_udp_sender{0};
//    const boost::asio::ip::address mc_address;
    
//    UDPListener * a_udp_listener{0};
//    UDPListeners * udp_listeners{0};

    MCGroupSend * a_mcgroupsend{0};
    MCGroupReceive * a_mcreceiver{0};
    

    
    bool restore();
    
    Session * interkomm_session = 0;
    Profile * interkomm_profile = 0;
    
    static Interkomm* Kit(ZDB * a_zdb = 0);
    void operator=(Interkomm const&){};
    static Interkomm* m_pInstance;
    
    void init();
    
    Mixer * mixer;

};

typedef vector <Interkomm*> Interkomms;

#endif /* defined(__Engine__Interkomm__) */
