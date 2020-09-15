//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__SettingsView__
#define __Engine__SettingsView__
#include "Engine.h"
#include "ContentView.h"



class SettingsView : public ContentView {
public:
    SettingsView(ZDB * a_zdb, GLViews * views);
    ~SettingsView();
    
};

#endif /* defined(__Engine__SettingsView__) */
