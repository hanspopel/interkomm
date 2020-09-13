//
//  Role.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef Role_hpp
#define Role_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class Role {
    string name{};
    
    
public:
    static int ID;
    int id{0};

    Role();
    Role(string name);
    
    int _id();
    
};



#endif /* Role_hpp */
