//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ProfileView.h"


//constructor
ProfileView::ProfileView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views) {// legacy: ChannelViewContainer
    
    backgroundColor = GLTOrange();
    
    tag = PROFILE_VIEW_TAG;
}

//deconstructor
ProfileView::~ProfileView() {
    
}

