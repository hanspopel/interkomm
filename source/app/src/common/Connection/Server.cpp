//
//  Server.cpp
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "Server.h"
#ifdef __IOS__
#include "MidiManagerExternal.h"
#endif
#include "MidiManagerInternal.h"

#include "Interkomm.h"
//constructor
Server::Server(ZDB * a_zdb, TCPConnection * a_connection, TCPClientManager * a_manager) : TCPClientConnection(a_zdb, a_connection, a_manager) {

    server_version = addParameter("server_version", 0, 9999, 0, true, is_linear, new Callback([=](GLEvent * event){

    }));
    server_version->always_call_listener = true;
    script_version = addParameter("script_version", 0, 9999, 0, true, is_linear, new Callback([=](GLEvent * event){

    }));
    script_version->always_call_listener = true;
    live_detected = addParameter("live_detected", 0, 1, 0, true, is_linear, 0);
    live_detected->always_call_listener = true;
    ableton_running = addParameter("ableton_running", 0, 1, 1, true, is_linear, 0);
    ableton_running->always_call_listener = true;
    version_string = addParameter("version_string", 0, 1, 0, false, is_string, 0);
    ableton_version_int = addParameter("ableton version int", 0, 9999999, 0, true, is_linear, new Callback([=](GLEvent * event){

    }));
    
    //may_autoconnect->setValue(false);
    
    if (tcp_port) {
        add_callbacks();
    }
    
    add_callbacks();
    
    
}



//deconstructor
Server::~Server() {
    
}


void Server::add_callbacks() {
    
    
    tcp_port->cb_manager->add_callback("/request/device_info", [=] (const osc::ReceivedMessage &m) {

        Server * ptr = this;
        
                
        char buffer[4096];
        osc::OutboundPacketStream p(buffer, 4096);
        
        string device_name = get_device_name();
        string device_id = get_uuid();
        bool is_iphone = true;

        p << osc::BeginMessage("/device_added");
        p << device_id.c_str();
        p << device_name.c_str();
        p << is_iphone;
        p << osc::EndMessage;
        
        ptr->send(p.Data(), p.Size());
        
        
    });
    
    tcp_port->cb_manager->add_callback("/server/pong", [=] (const osc::ReceivedMessage &m) {
        
        if (!manager || !Interkomm::Kit()->connection_manager || gl->in_background->ivalue()) {
            return;
        }
        
        Server * ptr = this;
        dispatch->on_main([=]{
            
            bool server_found = false;
            
            //print("connection LOCK");
            manager->connection_lock->Lock();


            //print("connection UNLOCK");
            manager->connection_lock->Unlock();


            if (!server_found) {
                return;
            }
            #ifdef __IOS__
                            if (ifa_name == "en2") {
                                probably_usb = true;
                            }
            #endif
            is_alive = true;
            osc::ReceivedMessageArgumentIterator it = m.ArgumentsBegin();
            
            int32_t script_version = (it++)->AsInt32();
            parameterMap->at("script_version")->setValue(script_version);
            int32_t server_version = (it++)->AsInt32();
            parameterMap->at("server_version")->setValue(server_version);
            
            bool live_detected = ((it++)->AsInt32());
            parameterMap->at("live_detected")->setValue(live_detected);
            
            if (m.ArgumentCount() > 3) {
                
                version_a = (it++)->AsInt32();
                version_b = (it++)->AsInt32();
                version_c = (it++)->AsInt32();
            }
            if (m.ArgumentCount() > 6) {
                parameterMap->at("ableton_running")->setValue((it++)->AsInt32());
            }
            if (m.ArgumentCount() > 7) {
                bool is_usb_connection = (it++)->AsInt32();
                if (is_usb_connection != is_usb) {
                    is_usb = is_usb_connection;
                    manager->servers_updated->setValue(1);
                }
            }
            
            parameterMap->at("version_string")->setString(to_string(version_a) + "." + to_string(version_b) + "." + to_string(version_c));
            
            ableton_version_int->setValue(version_a * 100 + version_b * 10 + version_c);

            
            if (waits_for_autoconnect && !connected->ivalue() && !manager->current_server) {
                //waits_for_autoconnect = false;
                manager->current_server = this;
                print("auto-connecting from ServerTA");
                connect();
            }
        });
    });


    
}
