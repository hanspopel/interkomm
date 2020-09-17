//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ProfileDialog__
#define __Engine__ProfileDialog__
#include "GLView.h"

class Profile;
class ProfileDialog : public GLView {
public:
    ProfileDialog(ZDB * a_zdb, Profile * in_profile);
    ~ProfileDialog();
    
    void touchesMoved(GLTouch * touch);
    void touchesBegan(GLTouch * touch);
    
    Profile * current_profile;
};

#endif /* defined(__Engine__ProfileDialog__) */
