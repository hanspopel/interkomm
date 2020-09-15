//
//  tALayoutManager.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "LayoutManager.h"
#include "Interkomm.h"
#include "GLScreen.h"
#include "ConnectionManager.h"
#include "ZDBConsole.h"

//constructor
LayoutManager::LayoutManager(ZDB * a_zdb) : GLControl(a_zdb) {
    
    Ikomm = Interkomm::Kit();
    
    chain_extension_state = addParameter("Chain Extesion State", -1, 2, -1, true, is_linear, 0);
    chain_extension_state->last_value_private = 0;
    
    layout_selection_buttons = new TopBarButtons();
    content_views = new GLViews();
    


    
    main_view = new GLView(a_zdb);
    addSubview(main_view);
    
    
    channel_view_container = new ChannelViewContainer(a_zdb,content_views);
    network_settings_view = new NetworkSettingsView(a_zdb,content_views,Ikomm->connection_manager);
    settings_view = new SettingsView(a_zdb,content_views);
    
    top_bar = new TopBar(a_zdb,this);
    addSubview(top_bar);
    
    
    gl->is_landscape->add_listener(new Callback([=](GLEvent * event){
        apply_rotation();
    }));
    apply_rotation();
    
    pre_frame_block = [=] (CRect aRect) {
        setFrames();
    };
    
    setFrames();
}

//deconstructor
LayoutManager::~LayoutManager() {
    
}


void LayoutManager::change_main_view(int atag){
    if (gl->console->superview) {
        gl->close_console();
    }
}

void LayoutManager::setFrame(CRect aFrame) {
    GLView::setFrame(aFrame);
}

void LayoutManager::select_content_view(int a_tag){
    
    int btn_tag = a_tag;

    for (TopBarButton * a_btn:*layout_selection_buttons) {
        if (btn_tag != a_btn->tag) {
            a_btn->setValue(0);
        }
        else {
            a_btn->setValue(1);
        }
    }
    
    for (GLView * a_view:*content_views) {
        a_view->removeFromSuperview();
    }
    main_view->addSubview(content_views->at(a_tag));
    
}

void LayoutManager::apply_rotation(){
    if (gl->is_landscape->ivalue()) {
        top_bar->main_grid->setViewSize(SizeMake(top_bar->grid_size_x, 1));
    }
    else {
        top_bar->main_grid->setViewSize(SizeMake(top_bar->grid_size_x, 1));
    }
    
}


void LayoutManager::setFrames(){
    
    topbar_height = 70.0/gl->frame.size.height;
    sidebar_width = 0;
    browser_width = 1/5.;
    settings_width = 1/3.5;
    keyboard_height = 130/gl->frame.size.height;
    
    if (zdb->gl->is_phone->ivalue()) {
        browser_width = 1/3.5;
        topbar_height =  60.0/gl->frame.size.height;
    }
    
    topbar_frame = CRectMake(0, 0, 1, topbar_height);
    top_bar->setRelativeFrame(topbar_frame);
    main_view->setRelativeFrame(CRectMake(0, topbar_height, 1 - sidebar_width, 1 - topbar_height));
;
}
