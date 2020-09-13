//
//  TAServerView.cpp
//  touchAble Pro
//
//  Created by Christian Blomert on 08/11/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ServerView.h"
#include <sstream>
#include "Interkomm.h"

//constructor
ServerView::ServerView(ZDB * a_zdb, TCPClientConnection * a_server) : TCPClientConnectionView(a_zdb, a_server) {
    setShowsValue(true);
    setShowsTitle(true);
    //TASet * set = touchAble::Kit()->set;
    
    string usb_add_on = "";
#ifdef __IOS__
    if (a_server->ifa_name == "en2" || a_server->ifa_name == "en3" || a_server->ifa_name == "en4" || a_server->ifa_name == "en5" || server->is_usb) {
        usb_add_on = " USB";
        check_view->setImage(gl->imageWithName("usb_connected.png"));

        check_view->setImageOn(gl->imageWithName("usb_connected.png"));
    }
    else {
#endif
        check_view->setImage(gl->imageWithName("connection_icon.png"));
        check_view->setImageOn(gl->imageWithName("connection_icon.png"));
#ifdef __IOS__
    }
#endif

    
    if (a_server->name == "localhost") {
        check_view->setImage(gl->imageWithName("loop_icon_sidebar.png"));
        check_view->setImageOn(gl->imageWithName("loop_icon_sidebar.png"));
    }
    
    titleLabel->setText(a_server->name + usb_add_on);

    setShowsValue(true);
    valueLabel->textAlignment = GLTextAlignmentRight;
    
    GLGridView * bla_grid = new GLGridView(zdb, CRectMake(0, 0, 1/3., 1), SizeMake(1, 3),false,false,0,0);
    bla_grid->isTouchEnabled = false;
    addSubview(bla_grid);
    
    
    ip_label = new GLLabel(zdb, CRectMake(0, 0/2.0, 4/4., 1));
    ip_label->isTouchEnabled = false;
    ip_label->adapt_to_base = false;
    ip_label->font_size_level->setValue(4);
    ip_label->textAlignment = GLTextAlignmentCenter;
    ip_label->baseLine = GLBaselineCenter;
    ip_label->setText(a_server->ip);
    addSubview(ip_label);

    server_version_status = new GLLabel(zdb, CRectMake(0, 0/2.0, 1/4., 1));
    server_version_status->isTouchEnabled = false;
	server_version_status->adapt_to_base = false;
	server_version_status->font_size_level->setValue(server_version_status->font_size_level->value());
    server_version_status->textAlignment = GLTextAlignmentLeft;
    server_version_status->baseLine = GLBaselineBottom;
    bla_grid->addSubview(server_version_status,0,0);
    server_version_status->setText("N/A");
    
    control_surface_status = new GLLabel(zdb, CRectMake(1/4.0, 0, 1/4.0, 1));
    control_surface_status->adapt_to_base = false;
    control_surface_status->isTouchEnabled = false;
    control_surface_status->font_size_level->setValue(control_surface_status->font_size_level->value());
    control_surface_status->textAlignment = GLTextAlignmentLeft;
    control_surface_status->baseLine = GLBaselineBottom;
     bla_grid->addSubview(control_surface_status,0,1);
    control_surface_status->setText("N/A");
    app_version_status = new GLLabel(zdb, CRectMake(2/4.0, 0, 1/4.0, 1));
    app_version_status->isTouchEnabled = false;

    app_version_status->adapt_to_base = false;
    app_version_status->font_size_level->setValue(control_surface_status->font_size_level->value());
    app_version_status->textAlignment = GLTextAlignmentLeft;
    app_version_status->baseLine = GLBaselineBottom;
    app_version_status->setText("N/A");
    //bla_grid->addSubview(app_version_status,1,0);
    bla_grid->addSubview(valueLabel,0,2);
        app_version_status->isTouchEnabled = false;
    valueLabel->isTouchEnabled = false;

    
    
    status_label = new GLLabel(zdb, CRectMake(0, 0, 1, 1));
    status_label->adapt_to_base = false;
    status_label->font_size_level->setValue(control_surface_status->font_size_level->value());
    status_label->textAlignment = GLTextAlignmentCenter;
    status_label->baseLine = GLBaselineBottom;
    addSubview(status_label);
    
    
    network_label = new GLLabel(zdb, CRectMake(0, 0, 5/6.0, 1));
    network_label->adapt_to_base = false;
    network_label->font_size_level->setValue(control_surface_status->font_size_level->value());
    network_label->textAlignment = GLTextAlignmentRight;
    network_label->baseLine = GLBaselineCenter;
    addSubview(network_label);
    
    valueLabel->setRelativeFrame(CRectMake(3/4., 0, 1/4., 1));
    valueLabel->textAlignment = GLTextAlignmentLeft;
    valueLabel->baseLine = GLBaselineBottom;
    
    string main_minor_string = "0";

    app_version_status->setText("v." + main_minor_string + " APP");
    

	titleLabel->adapt_to_base = false;
	titleLabel->font_size_level->setValue(titleLabel->font_size_level->value() + 1);
    titleLabel->setRelativeFrame(CRectMake(0, 0, 1, 1));
    titleLabel->baseLine = GLBaselineTop;
    //check_view->setRelativeFrame(CRectMake(3/4., 0, 1/4., 1));
    
	valueLabel->adapt_to_base = false;
	valueLabel->font_size_level->setValue(control_surface_status->font_size_level->value());

    addCallbackForControlEvent(new Callback([=](GLEvent * event){
        
//        if (server && server->script_version->ivalue() >= set->minimum_script_version && server->server_version->ivalue() >= set->minimum_server_version && server->ableton_version_int->ivalue() >= set->minimum_live_version) {
//            server->connect();
//        }
        if (server) {
            server->connect();
        }
    }), GLControlEventTouchUpInside);
    
    backgroundColor = TAMidDarkGray();
    backgroundColorHighlight = TAMidGray();
    backgroundColorOn = TALightMidGray();
    
    //check_view->imageColorOn = TASuperDarkGray();
    //titleLabel->fontColorOn = TASuperDarkGray();
    //valueLabel->fontColorOn = TASuperDarkGray();
    
    loading_view = new GLView(zdb);
    loading_view->add_post_draw_cb(new Callback([=](GLEvent * event){
        CPoint cent = CPointMake(loading_view->frame.size.width/2., loading_view->frame.size.height/2.);
        loading_view->tagf  = loading_view->tagf + M_PI * 3/60.0;
        loading_view->GLDrawBorderedCircularSegment(cent, loading_view->maximumSquare.size.width/2-1, 4, 2/2.*M_PI + loading_view->tagf , 5/2.*M_PI + loading_view->tagf, GLTransparent(),  GLWhite(), 40);

        //printf("drawing circle..\n");
    }));
    loading_view->lazyDrawing = false;
    loading_view->setRelativeFrame(CRectMake(5/6.0, 0, 1/6.0, 1));
    

    
    server->notify_all_listeners();

    corners[0] = false;
    corners[1] = false;
    corners[2] = true;
    corners[3] = true;
    
    addSubview(check_view);
}

//deconstructor
ServerView::~ServerView() {
 
    delete check_view;
    delete control_surface_status;
    delete server_version_status;
    delete status_label;
    delete network_label;
    
    //touchAble::Kit()->set->set_loading->remove_listener(set_loading_cb);
    //delete set_loading_cb;
}

void ServerView::version_checker(){
    //TASet * set = touchAble::Kit()->set;

    bool can_connect = true;
    string warnings = "status: OK";
    string network_stats = "no server found";
    if (server) {
        std::string lat_ms = format("%.0f", server->latency->value());
        network_stats = lat_ms + " ms";
        
        if (server->latency->value() < 5) {
            network_label->fontColor = GLTGreen();
        }
        else if (server->latency->value() < 100) {
            network_label->fontColor = GLWhite();
        }
        else {
            network_label->fontColor = GLTRed();
        }
        
    }
//    status_label->setText(warnings);
//    network_label->setText(network_stats);
//
//    control_surface_status->fontColor = GLWhite();
//    server_version_status->fontColor = GLWhite();
//    app_version_status->fontColor = GLWhite();
//    valueLabel->fontColor = GLWhite();
//
//    if (server) {
//
//        if (server->connected->ivalue()) {
//            setValue(1);
//        }
//
//        if (!server->parameterMap->at("ableton_running")->ivalue() && !server->parameterMap->at("live_detected")->ivalue()) {
//            //control_surface_status->fontColor = GLTBlue();
//            status_label->setText("Ableton Live not running.");
//            control_surface_status->setText("v.0.000 CS");
//            control_surface_status->fontColor = GLTRed();
//            valueLabel->setText("v." + server->version_string->string_value + " Live");
//            if (server->ableton_version_int->ivalue() < 972) {
//                valueLabel->fontColor = GLTRed();
//            }
//            warnings = "Live not running";
//            can_connect = false;
//        }
//        else if (!server->parameterMap->at("live_detected")->ivalue()) {
//            control_surface_status->fontColor = GLTRed();
//            status_label->setText("Control Surface not responding");
//            warnings = "Control Surfce not responding";
//            if (!server->parameterMap->at("ableton_running")->ivalue()) {
//                control_surface_status->fontColor = GLTRed();
//                status_label->setText("Ableton Live not running");
//                warnings = "Live not running";
//            }
//            can_connect = false;
//        }
//        else if (server->parameterMap->at("live_detected")->ivalue() && server->parameterMap->at("ableton_running")->ivalue()) {
            
//            if (server->parameterMap->at("script_version")->ivalue() >= set->minimum_script_version) {
//                control_surface_status->fontColor = GLWhite();
//            }
//            else {
//                control_surface_status->fontColor = GLTRed();
//                status_label->setText("Script Version Too Low");
//                can_connect = false;
//                warnings = "Script Version Too Low";
//            }
//
//            if (server->parameterMap->at("script_version")->ivalue() == 0) {
//                control_surface_status->fontColor = GLTRed();
//                status_label->setText("Control Surface not responding");
//                can_connect = false;
//                warnings = "Control Surfce not responding";
//            }
//
//            if (server->parameterMap->at("script_version")->ivalue() > 0 && server->server_version->ivalue() >= set->minimum_server_version) {
//                server_version_status->fontColor = GLWhite();
//            }
//            else {
//                server_version_status->fontColor = GLTRed();
//                status_label->setText("Script Version Too Low");
//                warnings = "Script Version Too Low";
//                can_connect = false;
//            }
//                if (server->ableton_version_int->ivalue() < 972) {
//                    valueLabel->fontColor = GLTRed();
//                    status_label->setText("Update Live");
//                    warnings = "Please Update Live to 9.7.2+";
//                    can_connect = false;
//                }

            
//            if (can_connect) {
//                if (set->client_app_version > server->server_version->ivalue()) {
//                    control_surface_status->fontColor = GLTOrange();
//                    server_version_status->fontColor = GLTOrange();
//                    //app_version_status->fontColor = GLTBlue();
//                    status_label->setText("Update Server and Scripts");
//                    warnings = "Update Server and Scripts";
//                    status_label->fontColor = GLTOrange();
//
//                }
//                else if (set->client_app_version < server->server_version->ivalue() - 10) {
//                    //control_surface_status->fontColor = GLTBlue();
//                    //server_version_status->fontColor = GLTBlue();
//                    app_version_status->fontColor = GLTOrange();
//                    status_label->setText("Please update App");
//                    status_label->fontColor = GLTOrange();
//                    warnings = "Please update App";
//                }
//                else {
//                    //control_surface_status->fontColor = GLTBlue();
//                    //server_version_status->fontColor = GLTBlue();
//                    //app_version_status->fontColor = GLTBlue();
//                    status_label->fontColor = GLTGreen();
//                }
//            }
//            else {
//                status_label->fontColor = GLTRed();
//            }
//
//        }
//
//    }
    

//    setNeedsDisplay(true);
}

void ServerView::parameter_of_host_changed(Parameter * a_parameter, ParameterHost * a_host) {
    
    if (!dispatch->is_on_main_thread()) {
        return;
    }
    
    //touchAble::Kit()->server_manager->connection_lock->Lock();
    
//        TASet * set = touchAble::Kit()->set;
        needsDisplay = true;
//            if (touchAble::Kit()->server_manager->removing_views || !server || !this || !isVisible) {
//                return;
//            }
            if (server->connected->ivalue()) {
                check_view->relativeImageFrame = CRectMake(5/6.0, 0, 1/6.0, 1);
                check_view->setRelativeFrame(check_view->relativeFrame);
                check_view->needsDisplay = true;
            }
            else {
                check_view->relativeImageFrame = CRectMake(5/6., 1/3., 1/6., 1/3.);
                check_view->setRelativeFrame(check_view->relativeFrame);
                check_view->needsDisplay = true;
            }
            if (a_parameter == server->connecting) {
                setHighlighted(server->connecting->ivalue() > 0);

                //printf("SERVER CONNECTING: %d\n", server->connecting->ivalue());
                
            }
            else if (a_parameter == server->connected) {
                setValue(server->connected->ivalue());
                //printf("SERVER CONNECTED: %d\n", server->connected->ivalue());
                if (server->connected->ivalue()) {
                    //valueLabel->removeFromSuperview();
                    loading_view->removeFromSuperview();
                    addSubview(check_view);
                    check_view->imageColorOn = GLTGreen();
                    check_view->imageColor = GLTGreen();
                }
                else {
                    loading_view->removeFromSuperview();
                    check_view->imageColor = GLWhite();
                    check_view->imageColorOn = GLWhite();
                    //check_view->removeFromSuperview();
                    //addSubview(valueLabel);
                }
            }
            else if (a_parameter == server->parameterMap->at("live_detected")) {
                
                if (!server->parameterMap->at("live_detected")->ivalue()) {
                    control_surface_status->fontColor = GLTRed();
                    status_label->fontColor = GLTRed();
                    //control_surface_status->setText("Control Surface not responding");
                    if (!server->parameterMap->at("ableton_running")->ivalue()) {
                        control_surface_status->fontColor = GLTRed();
                        status_label->fontColor = GLTRed();
                        //control_surface_status->setText("Ableton Live not running.");
                    }
                }
            }
            else if (a_parameter == server->parameterMap->at("ableton_running")) {
                if (!server->parameterMap->at("ableton_running")->ivalue() && !server->parameterMap->at("live_detected")->ivalue()) {
                    control_surface_status->fontColor = GLTRed();
                    status_label->fontColor = GLTRed();
                    //control_surface_status->setText("Ableton Live not running.");
                }
            }
            else if (a_parameter == server->version_string) {
                valueLabel->setText("v." + server->version_string->string_value + " Live");
                if (server->ableton_version_int->ivalue() < 972) {
                    valueLabel->fontColor = GLTRed();
                }
            }
            else if (a_parameter == server->parameterMap->at("script_version") && server->parameterMap->at("live_detected")->ivalue()) {
//                if (server->parameterMap->at("script_version")->ivalue() >= set->minimum_script_version) {
//                    control_surface_status->fontColor = GLWhite();
//                    app_version_status->fontColor = GLWhite();
//                }
//                else {
//                    control_surface_status->fontColor = GLTRed();
//                    app_version_status->fontColor = GLTRed();
//                    status_label->fontColor = GLTRed();
//                }
                
                int main_version = server->parameterMap->at("script_version")->ivalue() / 1000;
                int minor_version = (server->parameterMap->at("script_version")->ivalue() - main_version * 1000);
                
                control_surface_status->setText("v." + to_string(main_version) + "." + to_string(minor_version) + " CS");
                
                //only debug delete again
                //print("script version: %f", server->parameterMap->at("script_version")->value());
        //        control_surface_status->setText("v." + to_string(server->parameterMap->at("script_version")->value()) + " CS");
                //
                
                
                if (server->parameterMap->at("script_version")->ivalue() == 0) {
                    control_surface_status->fontColor = GLTRed();
                    status_label->fontColor = GLTRed();
                    //control_surface_status->setText("Control Surface not responding");
                    if (!server->parameterMap->at("ableton_running")->ivalue() && !server->parameterMap->at("live_detected")->ivalue()) {
                        control_surface_status->fontColor = GLTRed();
                        //control_surface_status->setText("Ableton Live not running.");
                        status_label->fontColor = GLTRed();
                    }
                }
            }
            else if (a_parameter == server->server_version) {
                int main_version = server->server_version->ivalue() / 1000;
                int minor_version = (server->server_version->ivalue() - main_version * 1000);
                server_version_status->setText("v." + to_string(main_version) + "." + to_string(minor_version) + " SRV");
                
            }
            version_checker();
        
   //touchAble::Kit()->server_manager->connection_lock->Unlock();

    
}

void ServerView::setValue(double aValue, bool feedback) {
    GLControl::setValue(aValue);
    check_view->setValue(aValue);
    titleLabel->setValue(aValue);
    valueLabel->setValue(aValue);
}
