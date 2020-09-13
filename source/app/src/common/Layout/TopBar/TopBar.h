//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__TopBar__
#define __Engine__TopBar__
#include "Engine.h"
#include "GLGridScrollView.h"
#include "TopBarButton.h"
#include "GLSettingsToggle.h"
#include "ConnectionView.h"
#include "GLPropertyList.h"

class LayoutManager;
class Studiomux;
class TopBar : public GLView {
public:
    TopBar(ZDB * a_zdb, LayoutManager * layout_manager);
    ~TopBar();
    
    int grid_size_x = 12;

    Studiomux * SMux = 0;
    
    GLGridScrollView * main_grid;
    
    TopBarButton * studiomux_button;
    TopBarButton * midimux_button;
    TopBarButton * oscmux_button;

    TopBarButton * settings_button;
    TopBarButton * audiobus_button;
    TopBarButton * browser_button;
    TopBarButton * help_button;

    TopBarButton * launch_ab_btn;
    TopBarButton * musical_keyboard_btn;
    TopBarButton * main_monitoring;
    TopBarButton * mixer_toggle;

    TopBarButton * server_status;

    void add_server_status_callbacks();
    
};

#endif /* defined(__Engine__TopBar__) */
