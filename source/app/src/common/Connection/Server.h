//
//  Server.h
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__Server__
#define __Engine__Server__
#include "Engine.h"
#include "ZDBObject.h"
#include "TCPCallbackManager.h"
#include "TCPClientConnection.h"
//#include <asio/io_context.hpp>


class Server : public TCPClientConnection {
public:
  
    Server(ZDB * a_zdb, TCPConnection * a_connection, TCPClientManager * a_manager);
    ~Server();
    
    void add_callbacks();
    bool probably_usb = false;


};

typedef vector <Server*> Servers;

#endif /* defined(__Engine__Server__) */
