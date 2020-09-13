//
//  MyMon.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__Studiomux__
#define __Engine__Studiomux__
#include "Engine.h"
#include "GLControl.h"
#include "MainView.h"
#include "TCPCallbackManager.h"
#include "ServerManager.h"
#include "ThreadMutex.h"
#include "TCPClient.h"
#include "CallbackManager.h"
#include "Server.h"


class Studiomux : public GLControl, public MidiDelegate, public ExternalMidiManagerDelegate  {
public:
    Studiomux(ZDB * a_zdb);
    ~Studiomux();
    
    MainView * main_view = 0;
    
    CThreadMutex * load_save_lock;
    
    TCPCallbackManager * callback_manager;
    ServerManager * server_manager;
    
    
    void save(string path);
    bool load(string path);
    
    
    Parameter * connected_to_server = 0;

    
    static Studiomux* Kit(ZDB * a_zdb = 0);
    void operator=(Studiomux const&){};
    static Studiomux* m_pInstance;
    
    void init();
    void setFrame(CRect aFrame);
    
    void save_session();

    


};

typedef vector <Studiomux*> Studiomuxs;

#endif /* defined(__Engine__Studiomux__) */
