//
//  User.hpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#ifndef User_hpp
#define User_hpp

 class Channel; // header files including each other

#include "StructureBase.h"


struct string_info {
    string profile_name = "Pascal";
    string display_name = "Pascal Kam";
    string display_tag = "veni venire";
    string display_profession = "veni venire";
    string uuid =  ".2";
};


class User : public StructureBase {

public :
    string extension = "users";


    string_info str_inf;
    
    User(ZDB * a_zdb);
    User(ZDB * a_zd, string name);
    void init();
    ~User(){};
    
    void talk(User* user); // 2 Buttons: 1xbel.User, 1xReturn
    void talk(Channel* channel);

    
    void assignPTThardware();
    
    void listentorec();
    
};



typedef vector <User*> Users;




#endif /* User_hpp */
