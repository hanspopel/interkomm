//
//  LayoutManager.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__LayoutManager__
#define __Engine__LayoutManager__
#include "Engine.h"
#include "GLControl.h"
#include "TopBar.h"
#include "TopBarButton.h"
#include "SettingsView.h"
#include "ChannelViewContainer.h"

class Interkomm;
class LayoutManager : public GLControl {
public:
    LayoutManager(ZDB * a_zdb);
    ~LayoutManager();

    GLView * main_view;
    GLView * content_view;
    TopBar * top_bar;
    
    bool keyboard_open = false;
    
    void top_bar_button_pressed(int atag);

    void setFrame(CRect aFrame);
    void setFrames();
        
    Interkomm * Ikomm = 0;
    
    ChannelViewContainer * channel_view_container;
    
    
    void change_main_view(int atag);
    
    TopBarButtons * layout_selection_buttons;
    GLViews * content_views;

    void select_content_view(int a_tag);
    

    
    SettingsView * settings_view;

    
    float topbar_height = 1;
    float sidebar_width = 0;
    float browser_width = 0;
    float settings_width = 0;
    float keyboard_height = 0;

    CRect topbar_frame = CRectMake(0, 0, 1, 1);
    
    int current_side_view = -1;
    int current_content_view = 0;
    
    void apply_rotation();

    Parameter * chain_extension_state = 0;
    
};

#endif /* defined(__Engine__LayoutManager__) */
