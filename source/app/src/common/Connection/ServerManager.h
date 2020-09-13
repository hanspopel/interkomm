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

class ServerManager : public TCPClientManager , public OSCDelegate, public TCPCallbackManagerDelegate, public USBPortConnectionDelegate {
public:
    ServerManager(ZDB * a_zdb, string opt_dns_search_term);
    ~ServerManager();
    
    Parameter * server_connected;
    Parameter * usb_connected;

    bool do_handle_message();

    long server_count = 0;
    int server_connected_count = 0;
    
    bool removing_views = false;
    
    
    void TCPConnectionAdded(TCPConnection * connection);
    void TCPConnectionRemoved(TCPConnection * connection);

    
    void receivedOSC(const osc::ReceivedMessage& m);
    void connectionClosed(USBPortConnection * port);
    void connectionOpened(USBPortConnection * port);
    
    double clock_drift = 0;
    double real_clock_drift = 1;

    double clock_drift_addition = 0;
    
    
//    Parameter * handshake;
    Parameter * version_match = 0;
    Parameter * host_name = 0;
    Parameter * device_name = 0;

    bool version_match_bool = true;
    
    int local_version = 210;
    int remote_version = 0;

    string device_id = "";
    
    CThreadMutex * audio_mutex;
    
    
};

typedef vector <ServerManager*> ServerManagers;

#endif /* defined(__Engine__ServerManager__) */
