//
//  User.cpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#include "User.h"
#include "Channel.h"
#include <stdio.h>


User::User(){
//    channel = new Channel();
    
    // TODO Link User to some kind of User-Account
    // Link User to PTT Buttons, except own User
    // User wird in Abhängigkeit von verbundenen Devices erzeugt, bekommt Daten von User-Device
        // wenn Verbindung verloren geht -> gleicher User. Wie?
    
    
    this->id = ID;
    ID++;
    cout << "Konstruktor User, ID :" << this->id << endl;
}

User::~User(){
    
//    delete channel;

std::cout << "\n Der User " << *this << "an der Speicherstelle  " << this << " wurde wieder entfernt \n";

}


User::User(string name){

//    channel = new Channel();
    this->id = ID;
    ID++;
    cout << "Konstruktor User (mit Name), ID :" << id << endl;
}

void User::talk(Channel* channel){

}

void User::talk(User* user){

}


void User::assignPTThardware(){
    
}

void User::listentorec(){ // chronologisch, nicht Userbezogen. Macht das SInn, was passiert wenn staendig gequatscht wird?
    
    
    // wird pausiert, wenn gesprochen wird
    
}

int User::_id(){

    return id;
}

ostream& operator<<(ostream& _cout, User& u){
    
    _cout << "id: " << u.id << " name: " << u.name << endl;

    return _cout;
}
