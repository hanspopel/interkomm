//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelDialog.h"
#include "Interkomm.h"

//constructor
ChannelDialog::ChannelDialog(ZDB * a_zdb, Session * a_session) : GLView(a_zdb) {
    
    
    backgroundColor = GLBlack();
    setIsPopupLayer(true);
    
    new_channel_name_label = new GLLabel(zdb,CRectMake(0, 0, 1, 0.1));
    
    gl->get_input("New Channel Name", [=]{
        if (gl->last_input != "") {
            new_channel_name = gl->last_input;
            new_channel_name_label->setText(new_channel_name);
            
            current_channel = new Channel(a_zdb,new_channel_name);
            a_session->_channels()->push_back(current_channel);
        }
        else {
            
        }
        
    }, [=]{});
    
    
    GLStyleButton * add_role = new GLStyleButton(a_zdb, "add role");
    add_role->colorOff = GLTRed();
    add_role->setRelativeFrame(CRectMake(0, 0.3, 1, 0.3));
    add_role->setIsPopupLayer(true);
    add_role->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
        gl->get_input("New Channel Name", [=]{
            if (gl->last_input != "") {
                current_channel->auto_add_role(gl->last_input);
            }
            else {
                
            }
            
        }, [=]{});
        
        
    }), GLControlEventTouchUpInside);
    addSubview(add_role);
    
    
    GLStyleButton * save_btn = new GLStyleButton(a_zdb, "save & exit");
    save_btn->colorOff = GLTRed();
    save_btn->setRelativeFrame(CRectMake(0, 0.9, 1, 0.1));
    save_btn->setIsPopupLayer(true);
    save_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
        char buffer[4096];
        osc::OutboundPacketStream p(buffer, 4096);
        p << osc::BeginMessage("/new_channel_created");
        p << new_channel_name.c_str();
        p << osc::EndMessage;
        
        Interkomm::Kit()->connection_manager->server->SendPacket(p.Data(), (int)p.Size(), NETWORK_DATA_OSC, 0 ,false);
        
        removeFromSuperview();
    }), GLControlEventTouchUpInside);
    addSubview(save_btn);
    
    
}

//deconstructor
ChannelDialog::~ChannelDialog() {
    
}
