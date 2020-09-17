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
    
    roles = new Roles();
    
}

void User::talk(Channel* channel){

}

void User::talk(User* user){

}





string User::create_string_from_user_profile(){
    
    string user_profile_string = "";
    user_profile_string.append(_name());
    user_profile_string.append(";");
    user_profile_string.append(_id());
    user_profile_string.append(";");
    for (Role * a_role:*_roles()) {
        user_profile_string.append(a_role->_name());
        user_profile_string.append(";");
    }
    user_profile_string.append(";");

    return user_profile_string;
}


void User::assignPTThardware(){
    
}

void User::listentorec(){ // chronologisch, nicht Userbezogen. Macht das SInn, was passiert wenn staendig gequatscht wird?
    

}

