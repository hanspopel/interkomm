//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "DebugView.h"

//constructor
DebugView::DebugView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb,content_views) {
    
    backgroundColor = GLTRed();
    
    network_settings = new NetworkDebugView(a_zdb);
    
    console_button = new dbButton(a_zdb);
    console_button->titleLabel->setText("console");
    console_button->setRelativeFrame(CRectMake(0, 0, 0.3, 0.1));
    console_button->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        console_button->setValue(!console_button->value);
        if (console_button->value) {
            gl->open_console();
        }
        else {
            gl->close_console();
        }
    }), GLControlEventTouchUpInside);
    addSubview(console_button);
    
    
}

//deconstructor
DebugView::~DebugView() {
    
}

