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



using namespace std;


class User : public StructureBase{

public :
    string extension = "users";

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
