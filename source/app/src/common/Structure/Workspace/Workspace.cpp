//
//  Channel.cpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#include "Workspace.h"

Workspace::Workspace(ZDB * a_zdb) : StructureBase(a_zdb) {
}

Workspace::Workspace(ZDB * a_zdb, string a_name) : StructureBase(a_zdb) {
    name_(a_name);
}
