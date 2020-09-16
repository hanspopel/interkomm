//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "StructureBase.h"

StructureBase::StructureBase(ZDB * a_zdb) : ZDBObject(a_zdb) {
}

StructureBase::StructureBase(ZDB * a_zdb, string a_name) : ZDBObject(a_zdb) {
    name = a_name;
}
