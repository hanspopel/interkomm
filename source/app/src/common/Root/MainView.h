//
//  MainView.h
//  MainView
//
//  Created by pascal kaap on 07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__MainView__
#define __Engine__MainView__
#include "Engine.h"
#include "GLControl.h"
#include "LayoutManager.h"


class MainView : public GLControl{
public:
    MainView(ZDB * a_zdb);
    ~MainView();

    
    LayoutManager * layout_manager = 0;
    

};


#endif /* defined(__Engine__MainView__) */
