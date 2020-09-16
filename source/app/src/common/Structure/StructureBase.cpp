//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "StructureBase.h"
#include "Session.h"

StructureBase::StructureBase(ZDB * a_zdb) : ZDBObject(a_zdb) {
}

StructureBase::StructureBase(ZDB * a_zdb, string a_name) : ZDBObject(a_zdb) {
    name = a_name;
}


string StructureBase::path_for_session(Session * a_session, string extension){
    string session_name = a_session->_name();
    return "/Sessions/" + session_name + "/" + session_name + "." + extension;
}
