//
//  Server.h
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__MCGroups__
#define __Engine__MCGroups__
#include "Engine.h"
#include "ZDBObject.h"
#include "TCPCallbackManager.h"
#include "TCPClientConnection.h"
//#include <asio/io_context.hpp>

#ifndef MAX_LEN
#define MAX_LEN 256
#endif

int setUDPNonblocking(int fd);

class OutboundInterface {
    
public:
    OutboundInterface();
    
};


class MCGroupReceive : public CThread{
  
private:
    string name{"testgroup"};
  
    int mc_sock{};                    /* socket descriptor */
    int flag_on{1};                   /* socket option flag */
    struct sockaddr_in mc_addr;       /* socket address structure */
    char recv_str[MAX_LEN + 1];       /* buffer to receive string */
    int recv_len{};                   /* length of string received */
    struct ip_mreq mc_req;            /* multicast request structure */
    char * mc_addr_str;               /* multicast IP address */
                               unsigned short mc_port{};         /* multicast port */
    struct sockaddr_in from_addr;     /* packet source */
    unsigned int from_len{};          /* source addr length */
//    WSADATA wsaData;                  /* Windows socket DLL structure */

    
    
    
public:
    MCGroupReceive();
    ~MCGroupReceive();
    
    virtual void Start();
    
    void init();
    
    void join_group();
    
    void receive();
    
    void leave_group(string group_name);
    
};






#endif /* defined(__Engine__MCGroups__) */
