//
//  User.hpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#ifndef User_hpp
#define User_hpp

 class Channel; // header files including each other

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>


using namespace std;


class User {
    string name{"Hugo"};
    int id;

//    Channel* channel;
    
    // TODO hat Account mit
            // e-mail ?
            // username  / passwort
            //
public :
 //   vector<Role> roles;
    static int ID;
    
    User();
    ~User();

    // TODO mit jedem User wird ein Button in der GUI erzeugt
    // Anordnung der Buttons für jede Anzahl Sprecher festlegen
    
    User(string name);

    
    friend ostream& operator<<(ostream& _cout, User& u);
    
    
    void talk(User* user); // 2 Buttons: 1xbel.User, 1xReturn
    void talk(Channel* channel);

    
    void assignPTThardware();
    
    void listentorec();
    
    int _id();
    
};







#endif /* User_hpp */
