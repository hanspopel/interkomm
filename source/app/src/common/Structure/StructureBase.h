//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef a_StructureBase
#define a_StructureBase


#include "Engine.h"
#include "mss.h"
class Session;
class StructureBase : public ZDBObject{
    string name;
    string unique_id;
public:

    StructureBase(ZDB * a_zdb);
    StructureBase(ZDB * a_zdb, string a_name);
    
    string _name(){return name;};
    void name_(string a_name){name = a_name;};

    string _id(){return unique_id;};
    void id_(string an_uid){unique_id = an_uid;};
    
    static string path_for_session(Session * a_session, string extension);
    
};

#endif /* StructureBase */
