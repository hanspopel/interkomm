//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "TopBar.h"
#include "Studiomux.h"

//constructor
TopBar::TopBar(ZDB * a_zdb, LayoutManager * layout_manager) : GLView(a_zdb) {
    
    backgroundColor = GLTransparent();
    
    SMux = Studiomux::Kit();
    
    add_pre_draw_cb(new Callback([=](GLEvent * event){
        colorGL = GLWhite();
        GLDrawRect(CRectMake(0, frame.size.height-1, frame.size.width, 1));
    }));
    
    main_grid = new GLGridScrollView(a_zdb,CRectMake(0, 0, 1, 1));
    main_grid->setGridSize(SizeMake(grid_size_x, 1));
    main_grid->setViewSize(SizeMake(grid_size_x, 1));
    main_grid->spacingY = 0;
    main_grid->spacingTop = 0;
    main_grid->spacingBottom = 0;
    main_grid->spacing_top = 0;
    main_grid->spacing_bottom = 0;
    main_grid->backgroundColor = GLTransparent();
    addSubview(main_grid);
    
    
    
    
    studiomux_button = new TopBarButton(a_zdb,"audiomux_topbar.png", layout_manager, 0);
    studiomux_button->setValue(1);
    midimux_button = new TopBarButton(a_zdb,"midimux_topbar.png", layout_manager, 1);
    oscmux_button = new TopBarButton(a_zdb,"oscmux_topbar.png", layout_manager, 2);
    browser_button = new TopBarButton(a_zdb,"browser_topbar.png", layout_manager, 10);
    help_button = new TopBarButton(a_zdb,"help_topbar.png", 0, -1);

    settings_button = new TopBarButton(a_zdb,"settings_topbar.png", layout_manager, 11);
    musical_keyboard_btn = new TopBarButton(a_zdb,"mute_icon.png", layout_manager, 20);
    //launch_ab_btn = new TopBarButton(a_zdb,"audiobus_icon.png");
    //main_monitoring = new TopBarButton(a_zdb,"monitor_icon.png");
    
    al->audio_output_active->setValue(1);

    
    //mixer_toggle = new TopBarButton(a_zdb,"mixer_icon.png", layout_manager, 0);
    
    server_status = new TopBarButton(a_zdb,"solo_icon.png",0,-1,true, false);
    server_status->removeAllControlEventsForType(GLControlEventTouchUpInside);
    server_status->removeAllControlEventsForType(GLControlEventTouchDown);
    server_status->token = "TAConnectionPopup";
    server_status->control_title = "Connection Status";
    server_status->setImage(gl->imageWithName("solo_icon.png"));
    server_status->setImageOn(gl->imageWithName("solo_icon.png"));
    server_status->imageColorHigh = TAExtremeLightGray();
    server_status->highlightsWhenTouched = false;
    server_status->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
//        if (SMux && SMux->server_manager && SMux->server_manager->servers) {
//            for (TCPClientConnection * a_server:*(SMux->server_manager)->servers) {
//                a_server->disconnect();
//            }
//            for (TCPClientConnection * a_server:*(SMux->server_manager)->servers) {
//                if (!a_server->connected->ivalue()) {
//                    a_server->connect();
//                    return;
//                }
//            }
//            //SMux->server_manager->servers->at(0)->connect();
//        }
        
//        if (TA && TA->set) {
//        }
            server_status->control_title = "Connection Status || v. " + string("0");

            gl->open_property_list(server_status, [=]{
        });
        
    }), GLControlEventTouchUpInside);
    
    
    ConnectionView * connection_view = new ConnectionView(zdb);
    connection_view->update_block = [=]{
        int size = connection_view->update();
        connection_view->tagf = size;
        gl->property_list->top = true;
    };
    gl->register_property("TAConnectionPopup", connection_view);
    
    
    
    
    
    main_grid->addSubview(studiomux_button, 0, 0);
    main_grid->addSubview(midimux_button, 1, 0);
    main_grid->addSubview(oscmux_button, 2, 0);
    main_grid->addSubview(browser_button, 3, 0);
    main_grid->addSubview(help_button, 4, 0);

    main_grid->addSubview(musical_keyboard_btn, 6, 0);
    //main_grid->addSubview(launch_ab_btn, 7, 0);
    //main_grid->addSubview(main_monitoring, 8, 0);
    //main_grid->addSubview(mixer_toggle, 9, 0);
    main_grid->addSubview(settings_button, 10, 0);
    main_grid->addSubview(server_status, 11, 0);
    
    add_server_status_callbacks();
}

//deconstructor
TopBar::~TopBar() {
    
}

void TopBar::add_server_status_callbacks(){
    
    Callback * servers_updated = new Callback([=](GLEvent * event){
        bool complete_server_found = true;
        
        SMux->server_manager->connection_lock->Lock();
        complete_server_found = SMux->server_manager->server_count;
        TCPClientConnection * current_server = 0;
        for (TCPClientConnection * aserver : *SMux->server_manager->servers) {
            if (aserver->is_usb) {
                current_server = aserver;
            }
            complete_server_found = true;
            break;
        }
        if (!complete_server_found) {
            for (TCPClientConnection * aserver : *SMux->server_manager->servers) {
                current_server = aserver;
                complete_server_found = true;
                break;
            }
        }
        
        SMux->server_manager->connection_lock->Unlock();
        
        if (current_server) {
            current_server->connect();
        }
        
        if (!complete_server_found) {
            server_status->imageColor = TARed();
            server_status->imageColorOn = TARed();
        }
        else {
            server_status->imageColor = TABlue();
            server_status->imageColorOn = TABlue();
        }
        server_status->needsDisplay = true;
    });
    
    Callback * server_connected = new Callback([=](GLEvent * event){
        server_status->setImageOn(gl->imageWithName("connection_icon.png"));
        
        if (SMux->server_manager->server_connected->ivalue()) {
            server_status->setImageHighlight(gl->imageWithName("connection_icon.png"));
        }
        if (SMux->server_manager && SMux->server_manager->current_server && ( ((Server*)(SMux->server_manager->current_server))->probably_usb || SMux->server_manager->current_server->is_usb)) {
            server_status->setImageOn(gl->imageWithName("usb_connected.png"));
        }
        else {
            server_status->setImageHighlight(gl->imageWithName("connection_off_icon.png"));
        }
        server_status->setValue(SMux->server_manager->server_connected->ivalue());
        server_status->needsDisplay = true;
    });
    
    SMux->server_manager->server_connected->add_listener(server_connected);
    server_connected->call(0);
    
    SMux->server_manager->servers_updated->add_listener(servers_updated);
    
}
