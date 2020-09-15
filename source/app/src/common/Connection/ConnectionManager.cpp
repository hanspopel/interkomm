//
//  ServerManager.cpp
//  touchAble Pro
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ConnectionManager.h"
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
ConnectionManager::ConnectionManager(ZDB * a_zdb, int flags, string opt_dns_search_term) : TCPClientManager(a_zdb, flags, opt_dns_search_term) {
        
    server = new TCPServer(a_zdb, flags, opt_dns_search_term);
    server->Start();
    
    tcp_client->discovery->guid = server->discovery->guid;
    tcp_client->plugin_client = true;



    servers_updated = addParameter("servers updated", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){}));
    clients_updated = addParameter("clients updated", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){}));
    clients_updated->always_call_listener = true;
    servers_updated->always_call_listener = true;

    
}

//deconstructor
ConnectionManager::~ConnectionManager() {
    

}

void ConnectionManager::TCPConnectionAdded(TCPConnection * connection) {
    servers_updated->setValue(true);
}

void ConnectionManager::TCPConnectionRemoved(TCPConnection * connection){
    servers_updated->setValue(true);
}

