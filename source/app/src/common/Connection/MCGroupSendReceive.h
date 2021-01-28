//
//  Server.h
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__MCGroupsSendReceive__
#define __Engine__MCGroupsSendReceive__
#include <stdio.h>
#include "Engine.h"
#include "ZDBObject.h"

#include "TCPCallbackManager.h"
#include "TCPClientConnection.h"

//#include <asio/io_context.hpp>

#define MCGROUPPORT 55555
#define MCBUF_MAXLEN 256


class MCGroupSend{

    int sock;
    struct sockaddr_in addr;
    long rc;
    char buffer[MCBUF_MAXLEN];
    char * mcgroupAddress;
    // socket anlegen
        
    
public:
    MCGroupSend();
    void MCSend();
    
};





#endif /* defined(__Engine__MCGroupsSendReceive__) */
