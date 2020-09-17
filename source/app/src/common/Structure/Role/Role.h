//
//  Role.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef Role_hpp
#define Role_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "mss.h"
#include "StructureBase.h"

using namespace std;
class Role;
class Session;

typedef vector <Role*> Roles;

class Role: public StructureBase {
        
public:

    
    
    Role(ZDB * a_zdb);
    Role(ZDB * a_zdb, string aname);
    ~Role(){};
    
    void init();
    
    static bool save_role(mss * sesion, Role * a_role, ZDB * a_zdb);
    static Role * load_role(mss * sesion, ZDB * a_zdb);
    
    static bool save_roles(Session * a_session, ZDB * a_zdb);
    static bool load_roles(Session * a_session, ZDB * a_zdb);
    
    static string get_extension(){return "roles";};

};



#endif /* Role_hpp */
