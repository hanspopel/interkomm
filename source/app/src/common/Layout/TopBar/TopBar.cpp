//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "TopBar.h"
#include "Interkomm.h"

//constructor
TopBar::TopBar(ZDB * a_zdb, LayoutManager * layout_manager) : GLView(a_zdb) {
    
    backgroundColor = GLTransparent();
    
    IKom = Interkomm::Kit();
    
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
    
    
    
    communication_button = new TopBarButton(a_zdb,"audiomux_topbar.png", layout_manager, 0); // legacy name channel_button]
    communication_button->setValue(1);
    debug_button = new TopBarButton(a_zdb,"oscmuxview_icon.png", layout_manager, 1);
    settings_button = new TopBarButton(a_zdb,"settings_topbar.png", layout_manager, PROFILE_VIEW_TAG);


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
    

    main_grid->addSubview(communication_button, 0, 0);
    main_grid->addSubview(debug_button, 1, 0);
    main_grid->addSubview(settings_button, 2, 0);

    main_grid->addSubview(server_status, 3, 0);
    add_server_status_callbacks();
}

//deconstructor
TopBar::~TopBar() {
    
}

void TopBar::add_server_status_callbacks(){
    
    
}
