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
ChannelsView::ChannelsView(ZDB * a_zdb, Channels * a_channels, SettingsView * a_settings_view) : SettingsDetailBase(a_zdb, a_settings_view) {
    
    settings_view = a_settings_view;
    
    current_channels = a_channels;
    
    channel_button_map = new ChannelSetButtonMap();
    
    
    
    GLStyleButton * add_roll_btn = new GLStyleButton(a_zdb);
    add_roll_btn->titleLabel->setText("Add");
    add_roll_btn->setRelativeFrame(CRectMake(0.5,0,0.5,0.1));
    addSubview(add_roll_btn);
    add_roll_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
        ChannelDialog * channel_dialog = new ChannelDialog(zdb, Interkomm::Kit()->interkomm_session);
        addSubview(channel_dialog);
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
        bool channel_found = false;
        for (Channel * a_channel:*current_channels) {
            if (new_channel_name == a_channel->_name()) {
                channel_found = true;
                break;
            }
        }
        if (!channel_found) {
            current_channels->push_back(new Channel(zdb, new_channel_name));
        }
        
        Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
        
        dispatch->on_main_if([=]{
            channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
            channels_scroll_view->loadVisibleGrid();
        });
        
    });
    
    Interkomm::Kit()->connection_manager->server->cb_manager->add_callback("/channel_update", [=](const osc::ReceivedMessage& m){
        
        
        osc::ReceivedMessageArgumentIterator it = m.ArgumentsBegin();
        string new_channel_name = (it++)->AsString();
        
        Channel * this_channel = 0;
        
        bool channel_found = false;
        for (Channel * a_channel:*current_channels) {
            if (new_channel_name == a_channel->_name()) {
                this_channel = a_channel;
                channel_found = true;
                break;
            }
        }
        if (!channel_found) {
            this_channel = new Channel(zdb, new_channel_name);
            current_channels->push_back(this_channel);
        }
        
        int user_size = (it++)->AsInt32();
        for (int i = 0; i < user_size; i++) {
            string new_user = (it++)->AsString();
            this_channel->auto_add_user(new_user);
        }
        
        int role_size = (it++)->AsInt32();
        for (int i = 0; i < role_size; i++) {
            string new_role = (it++)->AsString();
            this_channel->auto_add_role(new_role);
        }

        for (Role * a_role:*Interkomm::Kit()->interkomm_profile->_roles()) {
            for (Role * an_role:*this_channel->_roles()) {
                if (an_role->_name() == a_role->_name()) {
                    this_channel->auto_add_user(Interkomm::Kit()->interkomm_profile->_name());
                }
            }
        }
        
        Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
        
        dispatch->on_main_if([=]{
            channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
            channels_scroll_view->loadVisibleGrid();
        });
        
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
        
        dispatch->on_main_if([=]{
            channels_scroll_view->loadVisibleGrid();
        });
    });
    
    
}

//deconstructor
ChannelsView::~ChannelsView() {
    
}




void ChannelsView::add_channel(){
    
    
    
//    gl->get_input("New Pad Name", [=]{
//        if (gl->last_input != "") {
//            string channel_name = gl->last_input;
//
//            bool channel_exists = false;
//            for (Channel * a_channel:*current_channels) {
//                if (channel_name == a_channel->_name()) {
//                    channel_exists = true;
//                    break;
//                }
//            }
//            if (!channel_exists) {
//                current_channels->push_back(new Channel(zdb, channel_name));
//                Channel::save_channels(Interkomm::Kit()->interkomm_session, zdb);
//                channels_scroll_view->setGridSize(SizeMake(1, current_channels->size()));
//                channels_scroll_view->loadVisibleGrid();
//
//                char buffer[4096];
//                osc::OutboundPacketStream p(buffer, 4096);
//                p << osc::BeginMessage("/new_channel_created");
//                p << channel_name.c_str();
//                p << osc::EndMessage;
//
//                Interkomm::Kit()->connection_manager->server->SendPacket(p.Data(), (int)p.Size(), NETWORK_DATA_OSC, 0 ,false);
//            }
//
//        }
//        else {
//
//        }
//
//    }, [=]{});
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
