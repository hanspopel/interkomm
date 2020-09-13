//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Channel.h"

Channel::Channel(){

    this->id = ID;
    cout<<"Konstruktor Channel, ID :" << this->id << endl;

    ID++;
}

Channel::Channel(vector<Role*>* chanroles){

}


void Channel::setuproles(){

}


int Channel::_id(){

    return id;
}
