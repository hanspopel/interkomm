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
    
    IKomm = Interkomm::Kit();
    
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
    
    Callback * servers_updated = new Callback([=](GLEvent * event){
        dispatch->on_main_if([this]{
            connection_grid->removeAllSubviews();
            //print("connection LOCK");
            
            IKomm->connection_manager->connection_lock->Lock();
            
            long server_view_count = server_views->size() - 1;
            
            for (long i = server_view_count; i>= 0; i--) {
                GLView * serverV = server_views->at(i);
                server_views->erase(server_views->begin() + i);
                delete serverV;
            }
            
            server_views->clear();
            
                        
            for (TCPClientConnection * server : *IKomm->connection_manager->servers) {
                ServerView * server_view = new ServerView(zdb, server);
                server_views->push_back(server_view);
            }
            IKomm->connection_manager->connection_lock->Unlock();
            connection_grid->setGridSize(SizeMake(1, server_views->size()));
            connection_grid->loadVisibleGrid();
            if (isVisible) {
                gl->close_property_list();
            }
            
        });
        
        
    });
    
    IKomm->connection_manager->servers_updated->add_listener(servers_updated);
    servers_updated->call(0);
    
}

//deconstructor
ConnectionView::~ConnectionView() {
    
    
}

int ConnectionView::update() {
    connection_grid->setGridSize(SizeMake(1, server_views->size()));
    connection_grid->setViewSize(SizeMake(1, server_views->size()));
    return static_cast<int>(server_views->size());
}


