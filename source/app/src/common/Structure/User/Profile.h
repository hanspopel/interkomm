//
//  User.hpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#ifndef Profile_hpp
#define Profile_hpp
#include "User.h"

class Profile : public User {
public :

    Profile(ZDB * a_zdb);
    Profile(ZDB * a_zd, string name);
    void init();
    ~Profile(){};

    static Profile * load_profile(ZDB * a_zdb);
    static bool save_profile(Profile * a_profile, ZDB * a_zdb);

};

typedef vector <Profile*> Profiles;

#endif /* Profile_hpp */
