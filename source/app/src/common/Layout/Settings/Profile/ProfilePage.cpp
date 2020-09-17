//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ProfilePage.h"
#include "Interkomm.h"

//constructor
ProfilePage::ProfilePage(ZDB * a_zdb, Profile * a_profile) : GLView(a_zdb) {
    
    current_profile = a_profile;
    
    GLView * profile_overview = new GLView(a_zdb);
    profile_overview->backgroundColor = GLTBlue();
    addSubview(profile_overview);
    
    
    GLView * avatar_view = new GLView(a_zdb,CRectMake(0, 0, 1, 0.5));
    avatar_view->setImage(gl->imageWithName("ableton_link_disabled.png"));
    profile_overview->addSubview(avatar_view);
    
    GLGridView * profile_description_grid = new GLGridView(a_zdb, CRectMake(0, 0.5, 1, 0.5));
    profile_description_grid->setGridSize(SizeMake(2, 2));
    profile_overview->addSubview(profile_description_grid);
    
    GLLabel * profile_name_label = new GLLabel(a_zdb, current_profile->str_inf.profile_name);
    profile_description_grid->addSubview(profile_name_label, 0, 0);
    
    GLLabel * profile_profession_label = new GLLabel(a_zdb, current_profile->str_inf.display_profession);
    profile_description_grid->addSubview(profile_profession_label, 1, 0);
    
    GLLabel * profile_tag_label = new GLLabel(a_zdb, current_profile->str_inf.display_tag);
    profile_description_grid->addSubview(profile_tag_label, 0, 1);
    
    GLLabel * uuid_label = new GLLabel(a_zdb, current_profile->str_inf.uuid);
    profile_description_grid->addSubview(uuid_label, 1, 1);
    
    
    dbButton * change_profile_name = new dbButton(a_zdb);
    change_profile_name->setRelativeFrame(CRectMake(0.7, 0, 0.3, 0.2));
    change_profile_name->titleLabel->setText("change");
    profile_overview->addSubview(change_profile_name);
    change_profile_name->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        gl->get_input("New Pad Name", [=]{
            if (gl->last_input != "") {
                string new_profile_name = gl->last_input;
                Interkomm::Kit()->interkomm_profile->name_(new_profile_name);
                Profile::save_profile(Interkomm::Kit()->interkomm_profile, zdb);
            }
            else {
                
            }
            
        }, [=]{});
        
    }), GLControlEventTouchUpInside);
    
}

//deconstructor
ProfilePage::~ProfilePage() {
    
}
