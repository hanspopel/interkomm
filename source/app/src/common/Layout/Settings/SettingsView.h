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
#include "GLView.h"



class SettingsView : public GLView {
public:
    SettingsView(ZDB * a_zdb);
    ~SettingsView();
    
};

#endif /* defined(__Engine__SettingsView__) */
