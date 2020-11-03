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
    tcp_client->device_id = get_uuid();

    tcp_client->discovery->guid = server->discovery->guid;
    tcp_client->plugin_client = true;
    
    
    
    servers_updated = addParameter("servers updated", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){}));
    clients_updated = addParameter("clients updated", 0, 1, 0, true, is_linear, new Callback([=](GLEvent * event){}));
    clients_updated->always_call_listener = true;
    servers_updated->always_call_listener = true;
    
    
    gl->addTimerWithInterval(10, -1, [=]{
        broadcast_session();
    });
    

}

//deconstructor
ConnectionManager::~ConnectionManager() {
    
    
}

void ConnectionManager::work(){
    server->Start();
    tcp_client->Start();
}

void ConnectionManager::TCPConnectionAdded(TCPConnection * connection) {
    connection_lock->Lock();
    Server * server = new Server(zdb, connection, this);
//    broadcast_session();
    servers->push_back(server);
    server_count = servers->size();
    connection_lock->Unlock();
    servers_updated->setValue(1);
}

void ConnectionManager::TCPConnectionRemoved(TCPConnection * connection){
    
}

void ConnectionManager::broadcast_session(){

    for (Channel * a_channel:*Interkomm::Kit()->interkomm_session->_channels()) {
        char buffer[4096];
        osc::OutboundPacketStream p(buffer, 4096);
        p << osc::BeginMessage("/channel_update");
        string a_channel_name = a_channel->_name().c_str();
        int user_size = a_channel->_users()->size();
        int role_size = a_channel->_roles()->size();
        p << a_channel->_name().c_str();
        p << user_size;
        for (User * a_user:*a_channel->_users()) {
            p << a_user->_name().c_str();
        }
        p << role_size;
        for (Role * a_role:*a_channel->_roles()) {
            p << a_role->_name().c_str();
        }
        p << osc::EndMessage;
        Interkomm::Kit()->connection_manager->tcp_client->SendPacket(p.Data(), (int)p.Size(), NETWORK_DATA_OSC, 0 ,false);
    }
    
}
