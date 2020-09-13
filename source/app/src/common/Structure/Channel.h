//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef Channel_hpp
#define Channel_hpp


#include "User.hpp"
#include "SuperUser.hpp"
#include "Role.hpp"


#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Channel{
    
    string name;
    int id{0};
    
    vector<Role*> channelroles;
    
    int maxUsers{20};
    vector<User*> ChannelUsers{}; // spezialisierte SuperUser?
//    User* user{0};
    
public:
    static int ID;
    
    Channel();
    Channel(vector<Role*>* chanroles);

    
    void setuproles();
    
    int _id();
    
};



#endif /* Channel_hpp */
