//
//  User.cpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#include "User.h"
#include "Channel.h"


User::User(ZDB * a_zdb) : StructureBase(a_zdb){
    init();
}

User::User(ZDB * a_zdb, string a_name) : StructureBase(a_zdb, a_name){
    init();
}

void User::init(){
}

void User::talk(Channel* channel){

}

void User::talk(User* user){

}


void User::assignPTThardware(){
    
}

void User::listentorec(){ // chronologisch, nicht Userbezogen. Macht das SInn, was passiert wenn staendig gequatscht wird?
    

}
