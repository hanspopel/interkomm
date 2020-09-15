//
//  ConnectionManager.h
//  touchAble Pro
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ConnectionManager__
#define __Engine__ConnectionManager__
#include "Engine.h"
#include "ZDBObject.h"
#include "TCPClientManager.h"
#include "TCPServerManager.h"
#include <dns_sd.h>
#include "OSCDelegate.h"
#include "TCPServer.h"
#ifdef __IOS__
#include "USBPort.h"
#endif

class ConnectionManager: public ParameterHost, public TCPConnectionManagerDelegate {
public:
    ConnectionManager(ZDB * a_zdb, string opt_dns_search_term);
    ~ConnectionManager();
    
    TCPClientManager * client_manager;
    TCPServerManager * server_manager;

    TCPServer * server;
    TCPClient * client;

    void TCPConnectionAdded(TCPConnection * connection);
    void TCPConnectionRemoved(TCPConnection * connection);
    
    
    Parameter * servers_updated;
    Parameter * clients_updated;
};

typedef vector <ConnectionManager*> ConnectionManagers;

#endif /* defined(__Engine__ConnectionManager__) */
