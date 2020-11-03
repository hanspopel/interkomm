//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__RoleButton__
#define __Engine__RoleButton__
#include "Engine.h"
#include "ContentView.h"
#include "GLStyleButton.h"
#include "Role.h"


class RoleButton : public GLStyleButton {
public:
    RoleButton(ZDB * a_zdb, Role * a_role);
    ~RoleButton();
            
    GLStyleButton * delete_role_button;
    
    Role * role = 0;
};

#endif /* defined(__Engine__RoleButton__) */
