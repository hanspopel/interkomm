//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelsView.h"
#include "SettingsView.h"
#include "Interkomm.h"

//constructor
ChannelsView::ChannelsView(ZDB * a_zdb, Channels * a_channels, SettingsView * a_settings_view) : GLView(a_zdb) {
    
    settings_view = a_settings_view;
    
    current_channels = a_channels;
    
    channel_button_map = new ChannelSetButtonMap();
    
    
    dbButton * back_btn = new dbButton(a_zdb);
    back_btn->titleLabel->setText("Back");
    back_btn->setRelativeFrame(CRectMake(0,0,0.5,0.1));
    addSubview(back_btn);
    back_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        settings_view->back_to_overview();
    }), GLControlEventTouchUpInside);
    
    dbButton * add_roll_btn = new dbButton(a_zdb);
    add_roll_btn->titleLabel->setText("Add");
    add_roll_btn->setRelativeFrame(CRectMake(0.5,0,0.5,0.1));
    addSubview(add_roll_btn);
    add_roll_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        add_channel();
    }), GLControlEventTouchUpInside);
    
    
    channels_scroll_view = new GLGridScrollView(a_zdb, CRectMake(0, 0.15, 1, 0.85));
    channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
    channels_scroll_view->setViewSize(SizeMake(1, 4.5));
    addSubview(channels_scroll_view);
    channels_scroll_view->source_block = [=](int xx, int y, bool removing) {
        try {
            int x = y;
            string key = format("%d", x);
            if (removing) {
                ChannelButton * user_view = channel_button_map->at(key);
                channel_button_map->erase(key);
                user_view->should_delete = true;
                return user_view;
            }
            else if (x < current_channels->size()) {
                ChannelButton * user_view = new ChannelButton(a_zdb,current_channels->at(x));
                user_view->delete_channel_button->addCallbackForControlEvent(new Callback([=](GLEvent * event){
                    delete_channel(current_channels->at(x));
                }), GLControlEventTouchUpInside);
                channel_button_map->emplace(key, user_view);
                return user_view;
            }
            
        } catch (...) {
            return (ChannelButton*)nullptr;
            printf("failed source track_grid ");
        }
        return (ChannelButton*)nullptr;
    };
    
    channels_scroll_view->loadVisibleGrid();
    
    
    
    Interkomm::Kit()->connection_manager->tcp_client->cb_manager->add_callback("/new_channel_created", [=](const osc::ReceivedMessage& m){

        
        
        osc::ReceivedMessageArgumentIterator it = m.ArgumentsBegin();
        string new_channel_name = (it++)->AsString();

        current_channels->push_back(new Channel(zdb, new_channel_name));
        Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
        channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
        channels_scroll_view->loadVisibleGrid();
        
        
    });
    
    
    Interkomm::Kit()->connection_manager->tcp_client->cb_manager->add_callback("/channel_deleted", [=](const osc::ReceivedMessage& m){

        
        
        osc::ReceivedMessageArgumentIterator it = m.ArgumentsBegin();
        string new_channel_name = (it++)->AsString();

        int a_counter = 0;
        for (Channel * a_channel:*current_channels) {
            if (new_channel_name == a_channel->_name()) {
                current_channels->erase(current_channels->begin() + a_counter);
                delete a_channel;
            }
            a_counter++;
        }
        Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
        channels_scroll_view->loadVisibleGrid();
        
    });
    
    
}

//deconstructor
ChannelsView::~ChannelsView() {

}




void ChannelsView::add_channel(){
    gl->get_input("New Pad Name", [=]{
        if (gl->last_input != "") {
            string channel_name = gl->last_input;
            current_channels->push_back(new Channel(zdb, channel_name));
            Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
            channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
            channels_scroll_view->loadVisibleGrid();
            
            char buffer[4096];
            osc::OutboundPacketStream p(buffer, 4096);
            p << osc::BeginMessage("/new_channel_created");
            p << channel_name.c_str();
            p << osc::EndMessage;
            
            Interkomm::Kit()->connection_manager->server->SendPacket(p.Data(), (int)p.Size(), NETWORK_DATA_OSC, 0 ,false);
        }
        else {
            
        }
        
    }, [=]{});
}

void ChannelsView::delete_channel(Channel * a_delete_channel){
    int a_counter = 0;
    string channel_name = "";
    for (Channel * a_channel:*current_channels) {
        if (a_channel == a_delete_channel) {
            channel_name = a_channel->_name();
            current_channels->erase(current_channels->begin() + a_counter);
            delete a_delete_channel;
        }
        a_counter++;
    }
    Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
    channels_scroll_view->loadVisibleGrid();
    
    char buffer[4096];
    osc::OutboundPacketStream p(buffer, 4096);
    p << osc::BeginMessage("/channel_deleted");
    p << channel_name.c_str();
    p << osc::EndMessage;
    
    Interkomm::Kit()->connection_manager->server->SendPacket(p.Data(), (int)p.Size(), NETWORK_DATA_OSC, 0 ,false);
    
}
