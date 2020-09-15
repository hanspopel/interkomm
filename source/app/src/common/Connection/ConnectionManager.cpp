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
ConnectionManager::ConnectionManager(ZDB * a_zdb, string opt_dns_search_term) : ParameterHost(a_zdb) {
    
    int general_flags = NetworkInfo::can_process_audio | NetworkInfo::forbid_loopback;

    server = new TCPServer(a_zdb, general_flags, "Intercom from Space");
    server->Start();

    client = new TCPClient(a_zdb, general_flags | NetworkInfo::is_plugin, "Intercom from Space");
    client->discovery->guid = server->discovery->guid;
    client->delegate = this;
    client->Start();
        
//    client_manager = new TCPClientManager(a_zdb, general_flags | NetworkInfo::is_plugin,"Intercom from Space");
//    client->discovery->guid = server->discovery->guid;
//    client->Start();

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

