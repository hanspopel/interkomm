//
//  ServerManager.cpp
//  touchAble Pro
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ServerManager.h"
#include "CallbackManager.h"
#ifndef WIN32
#include <netdb.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#else 
#include <WS2tcpip.h>
#endif


#include "Interkomm.h"
#include "USBDefines.h"

//constructor
ServerManager::ServerManager(ZDB * a_zdb, string opt_dns_search_term){
    
    int flags = DataTypeFlags::can_process_midi | DataTypeFlags::can_process_audio;

    
    #ifdef __IOS__
    server = new TCPServer(a_zdb, flags, "" ,0);
    #else
    server = new TCPServer(a_zdb, flags, "Intercom from Space",0);
    #endif
        
    #ifndef __IOS__
        server->Start();
    #endif

    
    #ifdef __IOS__
        client = new TCPClient(a_zdb, "Intercom from Space",flags);
        client->Start();
    #endif
        
    
}

//deconstructor
ServerManager::~ServerManager() {
    

}
