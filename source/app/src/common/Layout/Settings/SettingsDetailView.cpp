//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "SettingsView.h"


//constructor
SettingsView::SettingsView(ZDB * a_zdb, GLViews * content_views) : ContentView(a_zdb, content_views) {// legacy: ChannelViewContainer
    
    backgroundColor = GLTOrange();
    tag = PROFILE_VIEW_TAG;
    
    float profile_overview_height = 0.3;
    float roles_overview_height = 0.7;
    
    GLView * profile_overview = new GLView(a_zdb, CRectMake(0, 0, 1, profile_overview_height));
    profile_overview->backgroundColor = GLTBlue();
    addSubview(profile_overview);
    
    
    GLView * avatar_view = new GLView(a_zdb,CRectMake(0, 0, 1, 0.5));
    avatar_view->setImage(gl->imageWithName("ableton_link_disabled.png"));
    profile_overview->addSubview(avatar_view);
    
    GLGridView * profile_description_grid = new GLGridView(a_zdb, CRectMake(0, 0.5, 1, 0.5));
    profile_description_grid->setGridSize(SizeMake(1, 3));
    profile_overview->addSubview(profile_description_grid);
    
    GLLabel * profile_name_label = new GLLabel(a_zdb, "Pascal");
    profile_description_grid->addSubview(profile_name_label, 0, 0);
    
    GLLabel * profile_profession_label = new GLLabel(a_zdb, "Director");
    profile_description_grid->addSubview(profile_profession_label, 0, 1);
    
    GLLabel * profile_tag_label = new GLLabel(a_zdb, "Always sunny in");
    profile_description_grid->addSubview(profile_tag_label, 0, 2);
    
    
    settings_overview = new GLView(a_zdb, CRectMake(0, profile_overview_height, 1, roles_overview_height));
    settings_overview->backgroundColor = GLTGreen();
    addSubview(settings_overview);
    
    settings_detail_view = new GLView(a_zdb, CRectMake(1, profile_overview_height, 1, roles_overview_height));
    settings_detail_view->backgroundColor = GLTRed();
    addSubview(settings_detail_view);
    
    settings_detail_content_view = new GLView(a_zdb, CRectMake(0, 0, 1, 1));
    settings_detail_content_view->backgroundColor = GLTOrange();
    settings_detail_view->addSubview(settings_detail_content_view);
    
    settings_scroll_view = new GLGridScrollView(a_zdb, CRectMake(0, 0, 1, 1));
    settings_scroll_view->setGridSize(SizeMake(1, 10));
    settings_scroll_view->setViewSize(SizeMake(1, 4.5));
    settings_overview->addSubview(settings_scroll_view);
    
    settings_buttons = new dbButtons;
    
    dbButton * roles_btn = new dbButton(a_zdb);
    roles_btn->titleLabel->setText("Roles");
    settings_scroll_view->addSubview(roles_btn,0,0);
    settings_buttons->push_back(roles_btn);
    
    dbButton * channels_btn = new dbButton(a_zdb);
    channels_btn->titleLabel->setText("Channels");
    settings_scroll_view->addSubview(channels_btn,0,1);
    settings_buttons->push_back(channels_btn);
    
    dbButton * edit_profile_btn = new dbButton(a_zdb);
    edit_profile_btn->titleLabel->setText("Edit Profle");
    settings_scroll_view->addSubview(edit_profile_btn,0,2);
    settings_buttons->push_back(edit_profile_btn);
    
    dbButton * settings_btn = new dbButton(a_zdb);
    settings_btn->titleLabel->setText("Settings");
    settings_scroll_view->addSubview(settings_btn,0,3);
    settings_buttons->push_back(settings_btn);
    
    int i = 0;
    for (dbButton * a_btn:*settings_buttons) {
        a_btn->tag = i;
        a_btn->addCallbackForControlEvent(new Callback([=](GLEvent * event){
            enter_detail_view(a_btn->tag);
        }), GLControlEventTouchUpInside);
        i++;
    }
    
        
    
    createDirectoryAtPath("/Settings/");
    createDirectoryAtPath("/Settings/Profile/");
    
    
    user_roles = new Roles;
    Role::load_roles("/Settings/Profile/roles.roles",user_roles,zdb);
    
    roles_view = new RolesView(a_zdb,user_roles,this);
    
    current_channels = new Channels();
    
    Channel::load_channels("/Settings/Profile/channels.channels",current_channels,zdb);
    channels_view = new ChannelsView(a_zdb,current_channels,this);
    
}

//deconstructor
SettingsView::~SettingsView() {
    
}

void SettingsView::load_profile(string path){
    
}

void SettingsView::save_profile(string path){
    
}

void SettingsView::setFrame(CRect aFrame){
    GLView::setFrame(aFrame);
    
}


void SettingsView::enter_detail_view(int tag){
    settings_detail_content_view->removeAllSubviews();
    
    switch (tag) {
        case 0:
            settings_detail_content_view->addSubview(roles_view);
            break;
        case 1:
        settings_detail_content_view->addSubview(channels_view);
        break;
            
        default:
            break;
    }
    
    settings_detail_view->animateFrame(CRectMake(0, 0.3, 1, 0.7), 0.2, false, false, false, 0, 0);
    settings_overview->animateFrame(CRectMake(-1, 0.3, 1, 0.7), 0.2, false, false, false, 0, 0);
    
}

void SettingsView::back_to_overview(){
    
    settings_overview->animateFrame(CRectMake(0, 0.3, 1, 0.7), 0.2, false, false, false, 0, 0);
    settings_detail_view->animateFrame(CRectMake(1, 0.3, 1, 0.7), 0.2, false, false, false, 0, 0);
    
}
