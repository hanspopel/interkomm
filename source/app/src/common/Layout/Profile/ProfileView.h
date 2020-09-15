//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ProfileView__ //TODO
#define __Engine__ProfileView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridScrollView.h"
#include "OverallView.h"
#include "ChannelView.h"

#define PROFILE_VIEW_TAG 3

class ProfileView : public ContentView {
public:
    ProfileView(ZDB * a_zdb, GLViews * content_views);
    ~ProfileView();
    
};

#endif /* defined(__Engine__ProfileView__) */
