//
//  UserView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "UserView.h"
#include "GLStyleButton.h"

//constructor
UserView::UserView(ZDB * a_zdb, User * a_user) : GLView(a_zdb) {
    
//    GLLabel * label = new GLLabel(a_zdb,a_user->_name());
//    addSubview(label);
    
    talk_button = new GLStyleButton(a_zdb);
    talk_button->titleLabel->setText(a_user->_name());
    talk_button->setRelativeFrame(CRectMake(0, 0, 1, 1)); // (Position Channelbutton, 0 ,
    // CRectMake(float x, float y, float width, float height)
    addSubview(talk_button);
}

//deconstructor
UserView::~UserView() {
    
}


