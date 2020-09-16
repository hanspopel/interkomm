//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__NetworkDebugView__
#define __Engine__NetworkDebugView__
#include "Engine.h"
#include "ContentView.h"
#include "ConnectionManager.h"
#include "ServerView.h"
#include "GLGridScrollView.h"



class NetworkDebugView : public GLView {
public:
    NetworkDebugView(ZDB * a_zdb);
    ~NetworkDebugView();
    
    ConnectionManager * connection_manager;
    
    GLLabels * server_views;
    GLLabels * client_views;

    GLGridScrollView * client_grid;
    GLGridScrollView * server_grid;

    
};

#endif /* defined(__Engine__NetworkDebugView__) */
