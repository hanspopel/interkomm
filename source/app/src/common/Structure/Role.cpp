//
//  Role.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Role.h"

Role::Role(){

    this->id = ID;
    cout<<"Konstruktor User ID :"<< this->id << endl;
    ID++;
}

int Role::_id(){

    return id;
}
