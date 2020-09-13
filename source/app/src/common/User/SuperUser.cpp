//
//  SuperUser.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "SuperUser.h"


SuperUser::SuperUser(){

//    this->id = ID;
    cout<<"Konstruktor SuperUser, ID :"<< this->_id() << endl;
//    ID++;
}


void SuperUser::openUserConfig(){

}


void SuperUser::openChannelConfig(){
    
}

void SuperUser::setRoles(){
    
}

SuperUser::~SuperUser(){
    std::cout << "\n Der (Super)user " << *this << "an der Speicherstelle  " << this << " wurde wieder entfernt \n";
}
