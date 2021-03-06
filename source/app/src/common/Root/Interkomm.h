//
//  MyMon.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__Interkomm__
#define __Engine__Interkomm__
#include "Engine.h"
#include "GLControl.h"
#include "MainView.h"
#include "TCPCallbackManager.h"
#include "ConnectionManager.h"
#include "ThreadMutex.h"
#include "TCPClient.h"
#include "CallbackManager.h"
#include "Server.h"
#include "Mixer.h"
#include "Session.h"
#include "Profile.h"
#include "ProfileDialog.h"


class Interkomm : public GLControl  {
public:
    
    Interkomm(ZDB * a_zdb);
    ~Interkomm();
    
    MainView * main_view = 0;
        
    ConnectionManager * connection_manager;
        
    bool restore();
    
    Session * interkomm_session = 0;
    Profile * interkomm_profile = 0;
    
    static Interkomm* Kit(ZDB * a_zdb = 0);
    void operator=(Interkomm const&){};
    static Interkomm* m_pInstance;
    
    void init();
    
    Mixer * mixer;

};

typedef vector <Interkomm*> Interkomms;

#endif /* defined(__Engine__Interkomm__) */
