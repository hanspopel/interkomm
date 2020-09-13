//
//  CallbackManager.cpp
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "CallbackManager.h"

//constructor
CallbackManager::CallbackManager(ZDB * a_zdb) : ZDBObject(a_zdb) {
    
    callback_dict = new OSCCallbackDict;
    messages_to_handle = new OSCMessages;
    handle_lock = new CThreadMutex;
    
    gl->addDisplayLinkCallback(new Callback([=](GLEvent * event){
        if (1) {
            //uint64_t stop_watch_start = start_stopwatch();
            handle_lock->Lock();
            OSCMessages messages_to_delete;
            double time_elapsed = 0;
            long messages_handled = 0;
            //double time_for_message = 0;
            //double last_time = 0;
            for (messages_handled = messages_handled_till_now; messages_handled < messages_to_handle->size() && time_elapsed < 5; messages_handled++) {
                
                osc::ReceivedMessage* m  = messages_to_handle->at(messages_handled);

                
//                if (m->was_handled) {
//                    continue;
//                }
                try {
                    OSCCallback cb = callback_dict->at(string(m->AddressPattern()));
                    cb(*m);
                } catch (...) {
                    
                    print("message failed:");
                    m->print();
                }
                
                messages_to_delete.push_back(m);
                //m->was_handled = true;
            }
            if (messages_handled == messages_to_handle->size()) {
                messages_handled_till_now = 0;
                long a_size = messages_to_handle->size() - 1;
                for (long i = a_size; i>=0; i--) {
                    osc::ReceivedMessage* m = messages_to_handle->at(i);
                    messages_to_handle->erase(messages_to_handle->begin() + i);
                    delete m;
                }
//                for (osc::ReceivedMessage* m : *messages_to_handle) {
//                    delete m;
//                }
                messages_to_handle->clear();
            }
            else {
                messages_handled_till_now = messages_handled;
            }
       
            
         
            handle_lock->Unlock();
        }
    }), 1);
}

//deconstructor
CallbackManager::~CallbackManager() {
    
    
}

void CallbackManager::add_callback(string key, OSCCallback block) {
  
    callback_dict->emplace(key, block);
    
}

void CallbackManager::call_callback(const osc::ReceivedMessage& m) {
    handle_lock->Lock();

    if (!strcmp(m.AddressPattern(), "/done")) {
        done = true;
        //printf("FINISHED LOADING\n\n\n\n");
        dispatch->on_main([=]{

        });

    }
    if (!strcmp(m.AddressPattern(), "/set/size")) {
        //printf("STARTING TO LOAD\n\n\n\n");
        dispatch->on_main([=]{

        });
    }
    osc::ReceivedMessage * mm = new osc::ReceivedMessage(m);
    messages_to_handle->push_back(mm);
    handle_lock->Unlock();
}

void CallbackManager::print_message(osc::ReceivedMessage * m) {
    
    printf("%s:\n", m->AddressPattern());
    osc::ReceivedMessageArgumentIterator it = m->ArgumentsBegin();

    for (int i = 0; i < m->ArgumentCount(); i++) {
        if ((it)->IsInt32()) {
            printf("    Argument %d: INT %d\n", i, (it++)->AsInt32());
        }
        else if ((it)->IsFloat()) {
            printf("    Argument %d: FLOAT %f\n", i, (it++)->AsFloat());
        }
        else if ((it)->IsDouble()) {
            printf("    Argument %d: FLOAT %f\n", i, (it++)->AsDouble());
        }
        else if ((it)->IsString()) {
            printf("    Argument %d: STRING %s\n", i, (it++)->AsString());
        }
    }
}
