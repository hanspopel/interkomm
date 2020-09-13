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
class Interkomm;
class TopBar : public GLView {
public:
    TopBar(ZDB * a_zdb, LayoutManager * layout_manager);
    ~TopBar();
    
    int grid_size_x = 4;

    Interkomm * IKom = 0;
    
    GLGridScrollView * main_grid;
    
    TopBarButton * channel_button;


    TopBarButton * server_status;

    void add_server_status_callbacks();
    
};

#endif /* defined(__Engine__TopBar__) */
