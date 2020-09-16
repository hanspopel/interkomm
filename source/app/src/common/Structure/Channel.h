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
typedef vector <Channel*> Channels;

class Channel : public ZDBObject{
    
    string name;
    int id{0};
    
    vector<Role*> channelroles;
    

    
//    int maxUsers{20};
//    User* user{0};
    
public:
    static int ID;

    Users * channel_users;
    
    Channel(ZDB * a_zdb);
    Channel(ZDB * a_zdb, string a_name);
    Channel(ZDB * a_zdb, vector<Role*>* chanroles);

    string _name(){return name;};

    void setuproles();
    
    int _id();
    
    static bool save_channel(mss * sesion, Channel * a_channel, ZDB * a_zdb);
    static Channel * load_channel(mss * sesion, ZDB * a_zdb);
    
    static bool save_channels(string path, Channels * a_channels, ZDB * a_zdb);
    static bool load_channels(string path, Channels * a_channels, ZDB * a_zdb);
    
    
};

#endif /* Channel_hpp */
