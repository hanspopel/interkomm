//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef a_Session
#define a_Session


#include "mss.h"
#include "StructureBase.h"

#include <stdio.h>
#include <string>
#include <vector>
#include "Channel.h"
#include "Role.h"

class Session;
typedef vector <Session*> Sessions;

class Session : public StructureBase{
    
    Channels * channels;
    Roles * roles;
    
public:
    
    Session(ZDB * a_zdb);
    Session(ZDB * a_zdb, string a_name);

    void init();

    Roles * _roles(){return roles;};
    Channels * _channels(){return channels;};

    static bool save_latest_session(string a_name, ZDB * a_zdb);
    static bool save_session(Session * a_session, ZDB * a_zdb);

    static Session * load_session(string path, ZDB * a_zdb);
    static Session * load_latest_session(ZDB * a_zdb);


};

#endif /* Session */
