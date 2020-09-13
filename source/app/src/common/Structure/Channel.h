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

class Channel{
    
    string name;
    int id{0};
    
    vector<Role*> channelroles;
    

    
    int maxUsers{20};
//    User* user{0};
    
public:
    static int ID;

    Users * channel_users;
    
    Channel();
    Channel(vector<Role*>* chanroles);

    
    void setuproles();
    
    int _id();
    
};

typedef vector <Channel*> Channels;



#endif /* Channel_hpp */
