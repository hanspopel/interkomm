//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef a_InterkommSession
#define a_InterkommSession


#include "mss.h"
#include "Engine.h"

#include <stdio.h>
#include <string>
#include <vector>

class InterkommSession;
typedef vector <InterkommSession*> InterkommSessions;

class InterkommSession : public ZDBObject{
    
    string name;

    
public:

    
    InterkommSession(ZDB * a_zdb);
    InterkommSession(ZDB * a_zdb, string a_name);

    string _name(){return name;};

    static bool save_session(mss * sesion, InterkommSession * a_session, ZDB * a_zdb);
    static InterkommSession * load_session(mss * sesion, ZDB * a_zdb);
    
    static bool save_sessions(string path, InterkommSessions * a_sessions, ZDB * a_zdb);
    static bool load_sessions(string path, InterkommSessions * a_sessions, ZDB * a_zdb);
    
    
};

#endif /* InterkommSession */
