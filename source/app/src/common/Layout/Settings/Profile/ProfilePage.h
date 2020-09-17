//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ProfilePage__
#define __Engine__ProfilePage__
#include "Engine.h"
#include "GLView.h"

class Profile;
class ProfilePage : public GLView {
public:
    ProfilePage(ZDB * a_zdb, Profile * a_profile);
    ~ProfilePage();
    
    Profile * current_profile;
};

#endif /* defined(__Engine__ProfilePage__) */
