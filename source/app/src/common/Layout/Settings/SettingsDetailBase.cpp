//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "SettingsDetailBase.h"
#include "SettingsView.h"


//constructor
SettingsDetailBase::SettingsDetailBase(ZDB * a_zdb, SettingsView * a_set_view) : GLView(a_zdb) {
  
    settings_view = a_set_view;
    
    GLStyleButton * back_btn = new GLStyleButton(a_zdb);
    back_btn->titleLabel->setText("Back");
    back_btn->setRelativeFrame(CRectMake(0,0,0.5,0.1));
    addSubview(back_btn);
    back_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        settings_view->back_to_overview();
    }), GLControlEventTouchUpInside);
    
    
}

//deconstructor
SettingsDetailBase::~SettingsDetailBase() {
    
}
