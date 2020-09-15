//
//  TAConnectionView.cpp
//  touchAble Pro
//
//  Created by Christian Blomert on 04.05.18.
//
//

#include "ConnectionView.h"
#include "ConnectionManager.h"
#include "Interkomm.h"

//constructor
ConnectionView::ConnectionView(ZDB * a_zdb) : GLView(a_zdb) {
    
    server_views = new ServerViews;
    
    connection_grid = new GLGridScrollView(zdb);
    
    connection_grid->source_block = [=](int x, int y, bool removing) {
        if (y < server_views->size()) {
            server_views->at(y)->round_corners = y == server_views->size()-1;
            return server_views->at(y);
        }
        return (ServerView*)nullptr;
    };
    connection_grid->spacingRight = false;
    connection_grid->spacingBottom = false;
    connection_grid->spacingTop = false;
    connection_grid->spacingX = 0;
    connection_grid->spacingY = 1;
    connection_grid->setViewSize(SizeMake(1, 5));
    
    addSubview(connection_grid);
    backgroundColor = TADarkGray();
    
//    Callback * servers_updated = new Callback([=](GLEvent * event){
//        dispatch->on_main_if([this]{
//            connection_grid->removeAllSubviews();
//            //print("connection LOCK");
//            
//            Studiomux::Kit()->server_manager->connection_lock->Lock();
//            Studiomux::Kit()->server_manager->removing_views = true;
//
//            //TA->server_manager->tcp_client->connection_remove_lock->Lock();
//            
//            long server_view_count = server_views->size() - 1;
//            
//            for (long i = server_view_count; i>= 0; i--) {
//                GLView * serverV = server_views->at(i);
//                server_views->erase(server_views->begin() + i);
//                delete serverV;
//            }
////
////            for (GLView * serverV : *server_views) {
////                delete serverV;
////            }
//            server_views->clear();
//            
//            
//            
//            
//            bool show_only_one_connection_type = false;
//            vector<TCPClientConnection*> shown_servers;
//            bool use_ipv4 = false;
//            bool use_ipv6 = !use_ipv4;
//            if (show_only_one_connection_type) {
//                
//                vector<string> client_ids;
//                for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                    auto it = find(client_ids.begin(), client_ids.end(), server->tcp_port->device_name->string_value);
//                    if (it == client_ids.end()) {
//                        client_ids.push_back(server->tcp_port->device_name->string_value);
//                    }
//                }
//                //a_server->ifa_name == "en2" || a_server->ifa_name == "en3" || a_server->ifa_name == "en4" || a_server->ifa_name == "en5"
//                
//                for (string client_id : client_ids) {
//                    if (use_ipv6) {
//                        bool ipv6_found = false;
//                         for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                             if (server->tcp_port->ipv6 && server->tcp_port->device_name->string_value == client_id) {
//                                 ipv6_found = true;
//                                 break;
//                             }
//                         }
//                         for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                             if (server->tcp_port->device_name->string_value == client_id && ((ipv6_found && server->tcp_port->ipv6) || (!ipv6_found && server->tcp_port->ipv4))) {
//                                 shown_servers.push_back(server);
//                             }
//                         }
//                    }
//                    else {
//                        bool ipv4_found = false;
//                         for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                             if (server->tcp_port->ipv4 && server->tcp_port->device_name->string_value == client_id) {
//                                 ipv4_found = true;
//                                 break;
//                             }
//                         }
//                         for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                             if (server->tcp_port->device_name->string_value == client_id && ((ipv4_found && server->tcp_port->ipv4) || (!ipv4_found && server->tcp_port->ipv6))) {
//                                 shown_servers.push_back(server);
//                             }
//                         }
//                    }
// 
//                }
//            }
//            else {
//                for (TCPClientConnection * server : *Studiomux::Kit()->server_manager->servers) {
//                    shown_servers.push_back(server);
//                }
//            }
//            
//            
//            
//            int minus = 0;
//            for (TCPClientConnection * server : shown_servers) {
//#ifdef __IOS__
////                if (server == TA->server_manager->usb_server && !TA->server_manager->usb_server->usb_port->is_connected) {
////                    continue;
////                }
////                if (server == TA->server_manager->usb_server) {
////                    continue;
////                }
//#endif      
//#ifdef WINSTORE
//                if (server->tcp_port->port == 13339 && !server->tcp_port->connection_status->ivalue()) {
//                    minus = 1;
//                    continue;
//                }
//#endif
//                ServerView * server_view = new ServerView(zdb, server);
//                server_views->push_back(server_view);
//            }
//            //TA->server_manager->tcp_client->connection_remove_lock->Unlock();
//            //print("connection UNLOCK");
//            Studiomux::Kit()->server_manager->connection_lock->Unlock();
//            Studiomux::Kit()->server_manager->removing_views = false;
//
//            connection_grid->setGridSize(SizeMake(1, server_views->size() - minus));
//            connection_grid->loadVisibleGrid();
//            if (isVisible) {
//                gl->close_property_list();
////                gl->open_property_list(Studiomux::Kit()->main_view->top_bar->server_status, [=]{
////                });
//            }
//
//        });
//
//
//    });
//    
//
//
//    Studiomux::Kit()->server_manager->servers_updated->add_listener(servers_updated);
//    servers_updated->call(0);

}

//deconstructor
ConnectionView::~ConnectionView() {
    
    
}

int ConnectionView::update() {
    connection_grid->setGridSize(SizeMake(1, server_views->size()));
    connection_grid->setViewSize(SizeMake(1, server_views->size()));

    return static_cast<int>(server_views->size());
}


