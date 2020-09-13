//
//  ServerManager.h
//  touchAble Pro
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ServerManager__
#define __Engine__ServerManager__
#include "Engine.h"
#include "ZDBObject.h"
#include "TCPClientManager.h"
#include <dns_sd.h>
#include "OSCDelegate.h"
#include "TCPServer.h"
#ifdef __IOS__
#include "USBPort.h"
#endif

class ServerManager {
public:
    ServerManager(ZDB * a_zdb, string opt_dns_search_term);
    ~ServerManager();
    
    TCPClient * client;
    
    TCPServer * server;
    
};

typedef vector <ServerManager*> ServerManagers;

#endif /* defined(__Engine__ServerManager__) */
