//
//  UserView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__UserView__
#define __Engine__UserView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "User.h"

class UserView : public GLView {
public:
    UserView(ZDB * a_zdb, User * a_user);
    ~UserView();

    User * user;
    
    GLStyleButton * talk_button;

};

typedef unordered_map <string, UserView*> UserViewDict;


#endif /* defined(__Engine__UserView__) */
