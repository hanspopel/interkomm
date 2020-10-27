//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ProfileDialog.h"
#include "Interkomm.h"

//constructor
ProfileDialog::ProfileDialog(ZDB * a_zdb, Profile * a_profile) : GLView(a_zdb) {
    
    isTouchEnabled = true;
    
    backgroundColor = GLTRed();
    current_profile = a_profile;
    
    GLLabel * profile_name_label = new GLLabel(a_zdb);
    profile_name_label->setText("Please Create a Profle");
    profile_name_label->setRelativeFrame(CRectMake(0, 0, 1, 0.1));
    addSubview(profile_name_label);
    
    GLStyleButton * user_name = new GLStyleButton(a_zdb, "set user name");
    user_name->setRelativeFrame(CRectMake(0, 0.1, 1, 0.1));
    user_name->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
        gl->get_input("New Pad Name", [=]{
            if (gl->last_input != "") {
                string channel_name = gl->last_input;
                current_profile->name_(channel_name);
                current_profile->str_inf.profile_name = channel_name;
            }
            else {
                
            }
            
        }, [=]{});
        
    }), GLControlEventTouchUpInside);
    addSubview(user_name);

    
    GLStyleButton * display_name = new GLStyleButton(a_zdb, "set displaye name");
    display_name->setRelativeFrame(CRectMake(0, 0.2, 1, 0.1));
    display_name->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
        gl->get_input("New Pad Name", [=]{
            if (gl->last_input != "") {
                string channel_name = gl->last_input;
                current_profile->str_inf.display_name = channel_name;
            }
            else {
                
            }
            
        }, [=]{});
        
    }), GLControlEventTouchUpInside);
    addSubview(display_name);
    
    
    GLStyleButton * prof_name = new GLStyleButton(a_zdb, "set prof name");
    prof_name->setRelativeFrame(CRectMake(0, 0.3, 1, 0.1));
    prof_name->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
        gl->get_input("New Pad Name", [=]{
            if (gl->last_input != "") {
                string channel_name = gl->last_input;
                current_profile->str_inf.profile_name = channel_name;
            }
            else {
                
            }
            
        }, [=]{});
        
    }), GLControlEventTouchUpInside);
    addSubview(prof_name);
    
    
        
    
    GLStyleButton * save_btn = new GLStyleButton(a_zdb, "save & exit");
    save_btn->setRelativeFrame(CRectMake(0, 0.5, 1, 0.1));
    save_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        //Interkomm::Kit()->main_view->layout_manager->settings_view
        Profile::save_profile(current_profile, zdb);
        gl->removePopup(this);
    }), GLControlEventTouchUpInside);
    addSubview(save_btn);
    
    
}

//deconstructor
ProfileDialog::~ProfileDialog() {
    
}

void ProfileDialog::touchesBegan(GLTouch * touch){
    GLView::touchesBegan(touch);
}


void ProfileDialog::touchesMoved(GLTouch * touch){
    GLView::touchesMoved(touch);
}
