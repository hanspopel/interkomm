//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef Channel_hpp
#define Channel_hpp


#include "User.h"
#include "SuperUser.h"
#include "Role.h"


#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Channel;
class Session;
typedef vector <Channel*> Channels;

class Channel : public StructureBase{
    
    Roles * channels_roles = 0;
    Users * channel_users;

public:
    

    Channel(ZDB * a_zdb);
    Channel(ZDB * a_zdb, string a_name);
    Channel(ZDB * a_zdb, vector<Role*>* chanroles);
    
    void auto_add_user(string a_name);
    void auto_add_role(string a_name);

    void init();
            
    static bool save_channel(mss * sesion, Channel * a_channel, ZDB * a_zdb);
    static Channel * load_channel(mss * sesion, ZDB * a_zdb);
    
    static bool save_channels(Session * a_session, ZDB * a_zdb);
    static bool load_channels(Session * a_session, ZDB * a_zdb);
    
    static string get_extension(){return "channels";};
    
    Roles * _roles(){return channels_roles;};
    Users * _users(){return channel_users;};
    
};

#endif /* Channel_hpp */
