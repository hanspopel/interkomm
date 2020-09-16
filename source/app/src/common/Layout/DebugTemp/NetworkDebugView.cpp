//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "NetworkDebugView.h"
#include "Interkomm.h"

//constructor
NetworkDebugView::NetworkDebugView(ZDB * a_zdb) : GLView(a_zdb) {
    
    backgroundColor = GLTGreen();
    connection_manager = Interkomm::Kit()->connection_manager;
    
    server_views = new GLLabels;
    client_views = new GLLabels;
    
    client_grid = new GLGridScrollView(zdb);
    client_grid->setRelativeFrame(CRectMake(0, 0.2, 0.5, 0.8));
    client_grid->source_block = [=](int x, int y, bool removing) {
        if (y < client_views->size()) {
            client_views->at(y)->round_corners = y == server_views->size()-1;
            return client_views->at(y);
        }
        return (GLLabel*)nullptr;
    };
    client_grid->setViewSize(SizeMake(1, 5));
    addSubview(client_grid);
    
    server_grid = new GLGridScrollView(zdb);
    server_grid->setRelativeFrame(CRectMake(0.5, 0.2, 0.5, 0.8));
    server_grid->source_block = [=](int x, int y, bool removing) {
        if (y < server_views->size()) {
            server_views->at(y)->round_corners = y == server_views->size()-1;
            return server_views->at(y);
        }
        return (GLLabel*)nullptr;
    };
    server_grid->setViewSize(SizeMake(1, 5));
    addSubview(server_grid);
    
    
    GLLabel * client_heading = new GLLabel(a_zdb, "Clients");
    client_heading->setRelativeFrame(CRectMake(0, 0, 0.5, 0.2));
    addSubview(client_heading);
    
    GLLabel * server_heading = new GLLabel(a_zdb, "Servers");
    server_heading->setRelativeFrame(CRectMake(0.5, 0, 0.5, 0.2));
    addSubview(server_heading);
    
    Callback * servers_updated = new Callback([=](GLEvent * event){
        dispatch->on_main_if([this]{
            server_grid->removeAllSubviews();
            
            long server_view_count = server_views->size() - 1;
            
            for (long i = server_view_count; i>= 0; i--) {
                GLView * serverV = server_views->at(i);
                server_views->erase(server_views->begin() + i);
                delete serverV;
            }
            server_views->clear();
            
            int minus = 0;
            for (TCPConnection * a_server :*connection_manager->tcp_client->connections) {
                GLLabel * server_view = new GLLabel(zdb, a_server->device_name->string_value);
                server_view->backgroundColor = GLTRed();
                server_views->push_back(server_view);
            }
            
            server_grid->setGridSize(SizeMake(1, server_views->size() - minus));
            server_grid->loadVisibleGrid();
            
        });
    });
    
    Callback * clients_updated = new Callback([=](GLEvent * event){
        dispatch->on_main_if([this]{
            client_grid->removeAllSubviews();
            
            long server_view_count = client_views->size() - 1;
            
            for (long i = server_view_count; i>= 0; i--) {
                GLView * serverV = client_views->at(i);
                client_views->erase(client_views->begin() + i);
                delete serverV;
            }
            client_views->clear();
            
            int minus = 0;
            for (TCPConnection * a_server :*connection_manager->server->connections) {
                string device_name = a_server->target_ip;
                GLLabel * server_view = new GLLabel(zdb, device_name);
                server_view->backgroundColor = GLTRed();
                client_views->push_back(server_view);
            }
            
            client_grid->setGridSize(SizeMake(1, client_views->size() - minus));
            client_grid->loadVisibleGrid();
            
        });
    });
    
    connection_manager->servers_updated->add_listener(servers_updated);
    servers_updated->call(0);
    
    
}

//deconstructor
NetworkDebugView::~NetworkDebugView() {
    
}

