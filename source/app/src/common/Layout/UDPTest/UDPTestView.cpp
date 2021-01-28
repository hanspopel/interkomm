//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "UDPTestView.h"
//#include "UDPServer.h"
#include "MCGroupSendReceive.h"



//constructor
UDPTestView::UDPTestView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views){
    
    backgroundColor = GLTRed();
 
    
    send_grid = new GLGridView(a_zdb, CRectMake(0.1, 0.1, 1, 0.5));
    addSubview(send_grid);
    
    send0 = new GLButton(a_zdb);
    send1 = new GLButton(a_zdb);
    send2 = new GLButton(a_zdb);

    send0->titleLabel->setText("Button 0");
    send0->backgroundColor = GLTYellow();
    
    send1->titleLabel->setText("Button 1");
    send1->backgroundColor = GLTYellow();

    send2->titleLabel->setText("Button 3");
    send2->backgroundColor = GLTYellow();

    
    send_grid->addSubview(send0, 0, 0);
    send_grid->addSubview(send1, 0, 1);
    send_grid->addSubview(send2, 0, 2);

    
    //
//    udp_send0 = new UDPSender(send_port, zdb);
//    udp_send1 = new UDPSender(send_port+2, zdb);
//    udp_send2 = new UDPSender(send_port+4, zdb);
    a_mcgroupsend0 = new MCGroupSend();

    
    send0->addCallbackForControlEvent(new Callback([=](GLEvent *event){
        a_mcgroupsend0->MCSend();
    }), GLControlEventTouchDown);
    

    send1->addCallbackForControlEvent(new Callback([=](GLEvent *event){
//        udp_send1->init();
    }), GLControlEventTouchDown);
    
    
    send2->addCallbackForControlEvent(new Callback([=](GLEvent *event){
//        udp_send2->init();
    }), GLControlEventTouchDown);

    
    
    recv_grid = new GLGridView(a_zdb, CRectMake(0.6, 0.1, 1, 0.5));
    addSubview(recv_grid);

    
    recv0 = new GLButton(a_zdb);
    recv1 = new GLButton(a_zdb);
    recv2 = new GLButton(a_zdb);

    
    recv0->backgroundColor = GLTYellow();

    recv1->backgroundColor = GLTYellow();

    recv2->backgroundColor = GLTYellow();


    
    recv_grid->addSubview(recv0, 0, 0);
    recv_grid->addSubview(recv1, 0, 1);
    recv_grid->addSubview(recv2, 0, 2);
    

    
    
}



//destructor
UDPTestView::~UDPTestView() {
    
    delete recv0;
    delete recv1;
    delete recv2;
    delete recv_grid;
    
    delete send0;
    delete send1;
    delete send2;
    delete send_grid;
    
//    delete udp_send0;
    
}


