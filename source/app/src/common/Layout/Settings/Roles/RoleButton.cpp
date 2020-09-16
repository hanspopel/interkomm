//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "RoleButton.h"

//constructor
RoleButton::RoleButton(ZDB * a_zdb, Role * a_role) : dbButton(a_zdb) {
    
    backgroundColor = GLTRed();
    role = a_role;
    titleLabel->setText(a_role->_name());
    
    
    delete_role_button = new dbButton(a_zdb);
    addSubview(delete_role_button);
    delete_role_button->setRelativeFrame(CRectMake(0.7, 0, 0.3, 1));
    delete_role_button->titleLabel->setText("X");

}

//deconstructor
RoleButton::~RoleButton() {
    
}

