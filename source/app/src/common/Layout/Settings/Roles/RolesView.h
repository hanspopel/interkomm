//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__RolesView__
#define __Engine__RolesView__

#include "SettingsDetailBase.h"
#include "Role.h"
#include "GLGridScrollView.h"
#include "RoleButton.h"

typedef unordered_map <string, RoleButton*> RoleButtonMap;

class SettingsView;
class RolesView : public SettingsDetailBase {
public:
    RolesView(ZDB * a_zdb, Roles * a_roles, SettingsView * a_settings_view);
    ~RolesView();
        
    RoleButtonMap * role_button_map;
    
    GLGridScrollView * roles_scroll_view;
    
    void add_role();
    void delete_role(Role * a_role);
    
    
    Roles * user_roles;
    

};

#endif /* defined(__Engine__RolesView__) */
