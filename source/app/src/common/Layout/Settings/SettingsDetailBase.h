//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__SettingsDetailBase__ //TODO
#define __Engine__SettingsDetailBase__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "Role.h"


class SettingsView;
class SettingsDetailBase : public GLView {
public:
    SettingsDetailBase(ZDB * a_zdb, SettingsView * a_set_view);
    ~SettingsDetailBase();

    SettingsView * settings_view = 0;
};

#endif /* defined(__Engine__SettingsDetailBase__) */
