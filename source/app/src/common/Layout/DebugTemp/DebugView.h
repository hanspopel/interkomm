//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__DebugView__
#define __Engine__DebugView__
#include "Engine.h"
#include "ContentView.h"
#include "dbButton.h"
#include "NetworkDebugView.h"


class DebugView : public ContentView {
public:
    DebugView(ZDB * a_zdb, GLViews * views);
    ~DebugView();
    
    NetworkDebugView * network_settings;
    
    dbButton * console_button;
    
};

#endif /* defined(__Engine__DebugView__) */
