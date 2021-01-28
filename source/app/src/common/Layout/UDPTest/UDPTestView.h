//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__UDPTestView__ //TODO
#define __Engine__UDPTestView__
#include "Engine.h"
#include "ContentView.h"
#include "GLGridView.h"
#include "GLButton.h"
#include "ChannelView.h"
#include "MCGroupSendReceive.h"


#define SEND_PORT    20000

// typedef unordered_map <string, GLStyleButton*> ChannelButtonMap;

class UDPSender;

class UDPTestView : public ContentView {
public:
    
//    OverallView * overall_view;

    uint16_t send_port{SEND_PORT};
    
    
    GLGridView * send_grid;
    
    GLButton * send0;
    GLButton * send1;
    GLButton * send2;

    GLGridView * recv_grid;
    
    GLButton * recv0;
    GLButton * recv1;
    GLButton * recv2;
    

//    UDPSender * udp_send0;
//    UDPSender * udp_send1;
//    UDPSender * udp_send2;

    MCGroupSend * a_mcgroupsend0;
    
    
    
    
    
    UDPTestView(ZDB * a_zdb, GLViews * content_views);
    ~UDPTestView();
    
    
    
//    GLViews * content_views;

    

};



#endif /* defined(__Engine__UDPTestView__) */
