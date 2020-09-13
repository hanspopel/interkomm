//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__TopBarButton__
#define __Engine__TopBarButton__
#include "Engine.h"
#include "GLButton.h"


class LayoutManager;
class TopBarButton : public GLButton {
public:
    TopBarButton(ZDB * a_zdb);
    TopBarButton(ZDB * a_zdb, string image_name, LayoutManager * amanager = 0, int atag = -1, bool is_a_momentary = false, bool add_cb = true);
    ~TopBarButton();
    
    LayoutManager * layout_manager;
};

typedef vector <TopBarButton*> TopBarButtons;


#endif /* defined(__Engine__TopBarButton__) */
