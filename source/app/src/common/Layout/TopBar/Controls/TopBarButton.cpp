//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "TopBarButton.h"
#include "LayoutManager.h"

//constructor
TopBarButton::TopBarButton(ZDB * a_zdb) : GLButton(a_zdb) {
    

    
}

TopBarButton::TopBarButton(ZDB * a_zdb, string image_name, LayoutManager * amanager, int atag, bool is_a_momentary, bool add_cb) : GLButton(a_zdb) {
   
    tag = atag;
    layout_manager = amanager;
    
    if (tag > -1 && layout_manager) {
        layout_manager->layout_selection_buttons->push_back(this);
    }
    
    titleLabel->removeFromSuperview();
    highlightsWhenTouched = true;

    makeTransparent();
    relativeImageFrame = GLFullRect();
    
    //is_momentary = is_a_momentary;
    setImage(a_zdb->gl->imageWithName(image_name));

    if (add_cb) {
        addCallbackForControlEvent(new Callback([=](GLEvent * event){
            setValue(!value);
            if (tag > -1 && layout_manager) {
                layout_manager->select_content_view(tag);
            }
        }), GLControlEventTouchUpInside);
    }
   
    makeTransparent();
    
    imageColor = TAExtremeLightGray();
    imageColorOn = TAOrange();
    imageColorHigh = TABlue();
    //imageColor = GLBlack();
}


//deconstructor
TopBarButton::~TopBarButton() {
    
}


