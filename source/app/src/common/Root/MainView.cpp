//
//  MainView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "MainView.h"
#include "Interkomm.h"

//constructor
MainView::MainView(ZDB * a_zdb) : GLControl(a_zdb) {
    
    layout_manager = new LayoutManager(a_zdb);
    addSubview(layout_manager);

    gl->orientation_mode->setValue(0);
    gl->auto_rotation_is_on->setValue(0);
    
    add_pre_draw_cb(new Callback([=](GLEvent * event){
        float alpha = 0.2;
        GLDrawRectWithColors(frame,GLColorWithAlpha(GLTBlue(), alpha) , GLColorWithAlpha(GLTYellow(), alpha), GLColorWithAlpha(GLTGreen(), alpha), GLColorWithAlpha(GLTRed(), alpha));
    }));
    
}

//deconstructor
MainView::~MainView() {
    
    delete layout_manager;
    
}
