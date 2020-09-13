//
//  CallbackManager.h
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__CallbackManager__
#define __Engine__CallbackManager__
#include "Engine.h"
#include "ZDBObject.h"
#include "Server.h"
#include "TCPCallbackManager.h"

class CallbackManager : public ZDBObject {
public:
    CallbackManager(ZDB * a_zdb);
    ~CallbackManager();
    
    OSCCallbackDict * callback_dict;
    OSCMessages * messages_to_handle;
    void add_callback(string key, OSCCallback block);
    void call_callback(const osc::ReceivedMessage& m);
    void print_message(osc::ReceivedMessage * m);

    CThreadMutex * handle_lock;
    
    long messages_handled_till_now = 0;

    bool done = false;
};

typedef vector <CallbackManager*> CallbackManagers;

#endif /* defined(__Engine__CallbackManager__) */
