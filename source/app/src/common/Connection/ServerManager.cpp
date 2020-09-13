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


#include "Studiomux.h"
#include "USBDefines.h"



//constructor
ServerManager::ServerManager(ZDB * a_zdb, string opt_dns_search_term) : TCPClientManager(a_zdb, DataTypeFlags::can_process_midi | DataTypeFlags::can_process_audio, opt_dns_search_term, true, 2345) {
    
    handshake = addParameter("Handshake", 0, 1, 0, true, is_linear, 0);
    version_match = addParameter("Version Match", 0, 1, 0, true, is_linear, 0);
    host_name = addParameter("Host Name", 0, 1, 0, true, is_linear, 0);
    device_name = addParameter("Device Name", 0, 1, 0, true, is_linear, 0);
    
    tcp_client->cb_manager->callback_manager_delegate = this;
    
    server_connected = addParameter("Server Connected", 0, 1, 0, true, is_linear, 0);
    usb_connected = addParameter("USB Connected", 0, 1, 0, true, is_linear, 0);
    
    tcp_client->discovery->allow_loopback = false;
    
    gl->addTimerWithInterval(1, -1, [=]{
        //servers_updated->setValue(1);
    });
    
}

//deconstructor
ServerManager::~ServerManager() {
    

}

bool ServerManager::do_handle_message() {
    return !gl->in_background->ivalue();
}


void ServerManager::TCPConnectionAdded(TCPConnection * connection) {
        connection_lock->Lock();
        Server * server = new Server(zdb, connection, this);
        servers->push_back(server);
        server_count = servers->size();
        connection_lock->Unlock();
        servers_updated->setValue(1);
}

void ServerManager::TCPConnectionRemoved(TCPConnection * connection){
    
    connection_lock->Lock();
    server_count = servers->size();
    connection_lock->Unlock();
    servers_updated->setValue(1);
    
}



void ServerManager::receivedOSC(const osc::ReceivedMessage& m){
    
}

void ServerManager::connectionClosed(USBPortConnection * port){
    
}

void ServerManager::connectionOpened(USBPortConnection * port){
    
}
