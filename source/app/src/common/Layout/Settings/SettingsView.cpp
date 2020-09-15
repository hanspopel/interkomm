//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "SettingsView.h"

//constructor
SettingsView::SettingsView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb,content_views) {
    
    backgroundColor = GLTBlue();

}

//deconstructor
SettingsView::~SettingsView() {
    
}

