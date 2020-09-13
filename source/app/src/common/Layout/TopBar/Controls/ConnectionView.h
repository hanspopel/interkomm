//
//  ConnectionView.h
//  touchAble Pro
//
//  Created by Christian Blomert on 04.05.18.
//
//

#ifndef __Engine_____ConnectionView_____
#define __Engine_____ConnectionView_____

#include "Engine.h"
#include "ServerView.h"
#include "GLGridScrollView.h"

class ConnectionView : public GLView {
public:
    ConnectionView(ZDB * a_zdb);
    ~ConnectionView();
    
    ServerViews * server_views;
    GLGridScrollView * connection_grid;
    
    int update();
};

typedef vector <ConnectionView*> ConnectionViews;

#endif /* defined(__Engine_____ConnectionView_____) */
