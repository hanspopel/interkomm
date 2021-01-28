//
//  Server.cpp
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "MCGroups.h"


OutboundInterface::OutboundInterface(){
    
}





int setUDPNonblocking(int fd)
{
    if (!fd) {
        return -1;
    }
    int flags;

    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    u_long winflags = 1;
#ifdef WIN32
    return  ioctlsocket(fd, FIONBIO, &winflags);
#else
    return  ioctlsocket(fd, F_IONBIO, &winflags);

#endif
#endif
}



MCGroupReceive::MCGroupReceive(){

    init();
    join_group();

}

MCGroupReceive::~MCGroupReceive(){

}



// Server
void MCGroupReceive::init(){

    mc_addr_str = "224.1.50.15";       /* arg 1: multicast ip address */
    mc_port = atoi("55555");           /* arg 2: multicast port number */

    
    /* create socket to join multicast group on */
    if ((mc_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket() failed");
        exit(1);
    }

    /* set reuse port to on to allow multiple binds per host */
    if ((setsockopt(mc_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&flag_on,
        sizeof(flag_on))) < 0) {
        perror("setsockopt() failed");
        exit(1);
    }

    
    /* construct a multicast address structure */
    memset(&mc_addr, 0, sizeof(mc_addr));
    mc_addr.sin_family = AF_INET;
    mc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    mc_addr.sin_port = htons(mc_port);

    
    /* bind multicast address to socket */
    if ((::bind(mc_sock, (struct sockaddr *) &mc_addr,
        sizeof(mc_addr))) < 0) {
        perror("bind() failed");
        exit(1);
    }
    
    // TODO
    // Channelname = Alias für Multicast Adresse

 //   setUDPNonblocking(mc_sock);
    
    work_block = [=]{receive();};
    
}

void MCGroupReceive::join_group(){
    
    /* construct an IGMP join request structure */
    mc_req.imr_multiaddr.s_addr = inet_addr(mc_addr_str);
    mc_req.imr_interface.s_addr = htonl(INADDR_ANY);

    /* send an ADD MEMBERSHIP message via setsockopt */
    if ((setsockopt(mc_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
        (char*)&mc_req, sizeof(mc_req))) < 0) {
        perror("setsockopt() failed");
        exit(1);
    }

}

void MCGroupReceive::receive(){
    
    for (;;) {

                        /* clear the receive buffers & structs */
        memset(recv_str, 0, sizeof(recv_str));
        from_len = sizeof(from_addr);
        memset(&from_addr, 0, from_len);

        /* block waiting to receive a packet */
        if ((recv_len = recvfrom(mc_sock, recv_str, MAX_LEN, 0,
            (struct sockaddr*)&from_addr, &from_len)) < 0) {
 //           cout<<"."<<endl;
            usleep(1000);
 //           perror("recvfrom() failed");
 //           exit(1);
        }

        /* output received string */
        printf("Received %d bytes from %s: ", recv_len,
            inet_ntoa(from_addr.sin_addr));
        printf("%s", recv_str);
    }

    /* send a DROP MEMBERSHIP message via setsockopt */
    if ((setsockopt(mc_sock, IPPROTO_IP, IP_DROP_MEMBERSHIP,
        (void*)&mc_req, sizeof(mc_req))) < 0) {
        perror("setsockopt() failed");
        exit(1);
    }

    closesocket(mc_sock);
    
}


void MCGroupReceive::Start(){
    
    CThread::Start();
    
}



// Clients (+ Server ?)
void MCGroupReceive::leave_group(string group_name){
    
    // TODO
}

