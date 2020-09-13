//
//  TAServerView.h
//  touchAble Pro
//
//  Created by Christian Blomert on 08/11/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__TAServerView__
#define __Engine__TAServerView__
#include "Engine.h"
#include "TCPClientConnectionView.h"
#include "TCPClientConnection.h"
#include "GLGridView.h"

class ServerView : public TCPClientConnectionView {
public:
    ServerView(ZDB * a_zdb, TCPClientConnection * a_server);
    ~ServerView();
    
    void parameter_of_host_changed(Parameter * a_parameter, ParameterHost * a_host);
    
    GLLabel * control_surface_status;
    GLLabel * server_version_status;
    GLLabel * app_version_status;
    
    GLLabel * ip_label;

    int last_valid_script = 1599;
    int last_valid_server = 1599;
    GLLabel * status_label;

    GLLabel * network_label;
    GLView * loading_view;
    
    void version_checker();
    
    void setValue(double aValue, bool feedback = false);
};

typedef vector <ServerView*> ServerViews;

#endif /* defined(__Engine__ServerView__) */
