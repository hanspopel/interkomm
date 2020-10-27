//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "RolesView.h"
#include "SettingsView.h"
#include "Interkomm.h"

//constructor
RolesView::RolesView(ZDB * a_zdb, Roles * a_roles, SettingsView * a_settings_view) : SettingsDetailBase(a_zdb, a_settings_view) {
    
    settings_view = a_settings_view;
    
    user_roles = a_roles;
    
    role_button_map = new RoleButtonMap();
    
    GLStyleButton * add_roll_btn = new GLStyleButton(a_zdb);
    add_roll_btn->titleLabel->setText("Add");
    add_roll_btn->setRelativeFrame(CRectMake(0.5,0,0.5,0.1));
    addSubview(add_roll_btn);
    add_roll_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        add_role();
    }), GLControlEventTouchUpInside);
    
    
    roles_scroll_view = new GLGridScrollView(a_zdb, CRectMake(0, 0.15, 1, 0.85));
    roles_scroll_view->setGridSize(SizeMake(1, user_roles->size()));
    roles_scroll_view->setViewSize(SizeMake(1, 4.5));
    addSubview(roles_scroll_view);
    roles_scroll_view->source_block = [=](int xx, int y, bool removing) {
        try {
            int x = y;
            string key = format("%d", x);
            if (removing) {
                RoleButton * user_view = role_button_map->at(key);
                role_button_map->erase(key);
                user_view->should_delete = true;
                return user_view;
            }
            else if (x < user_roles->size()) {
                RoleButton * user_view = new RoleButton(a_zdb,user_roles->at(x));
                user_view->delete_role_button->addCallbackForControlEvent(new Callback([=](GLEvent * event){
                    delete_role(user_roles->at(x));
                }), GLControlEventTouchUpInside);
                role_button_map->emplace(key, user_view);
                return user_view;
            }
            
        } catch (...) {
            return (RoleButton*)nullptr;
            printf("failed source track_grid ");
        }
        return (RoleButton*)nullptr;
    };
    
    roles_scroll_view->loadVisibleGrid();
    
    
    
}

//deconstructor
RolesView::~RolesView() {
    
}



void RolesView::add_role(){
    gl->get_input("New Pad Name", [=]{
        if (gl->last_input != "") {
            user_roles->push_back(new Role(zdb, gl->last_input));
            Role::save_roles(Interkomm::Kit()->interkomm_session, zdb);
            roles_scroll_view->setGridSize(SizeMake(1, user_roles->size()));
            roles_scroll_view->loadVisibleGrid();
        }
        else {
            
        }
        
    }, [=]{});
}

void RolesView::delete_role(Role * a_delete_role){
    int a_counter = 0;
    for (Role * a_role:*user_roles) {
        if (a_role == a_delete_role) {
            user_roles->erase(user_roles->begin() + a_counter);
            delete a_role;
        }
        a_counter++;
    }
    Role::save_roles(Interkomm::Kit()->interkomm_session, zdb);
    roles_scroll_view->loadVisibleGrid();
}
