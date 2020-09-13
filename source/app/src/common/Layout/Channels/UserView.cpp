//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "UserView.h"
#include "dbButton.h"

//constructor
UserView::UserView(ZDB * a_zdb, User * a_user) : GLView(a_zdb) {
    
    GLLabel * label = new GLLabel(a_zdb,a_user->_name());
    addSubview(label);
    
    talk_button = new dbButton(a_zdb);
    talk_button->titleLabel->setText("TALK");
    talk_button->setRelativeFrame(CRectMake(0.6, 0, 0.4, 1));
    addSubview(talk_button);
}

//deconstructor
UserView::~UserView() {
    
}


