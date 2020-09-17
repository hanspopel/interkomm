//
//  Channel.hpp
//  Intercom User structure
//
//  Created by Sascha Arlt on 08.09.20.
//  Copyright © 2020 Sascha Arlt. All rights reserved.
//

#ifndef a_Workspace
#define a_Workspace


#include "mss.h"
#include "StructureBase.h"

class Workspace;
typedef vector <Workspace*> Workspaces;

class Workspace : public StructureBase{

public:
    
    Workspace(ZDB * a_zdb);
    Workspace(ZDB * a_zdb, string a_name);
    
};

#endif /* Workspace */
