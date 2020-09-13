//
//  ContentView.h
//  MyMon
//
//  Created by pascal kaap on07/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#ifndef __Engine__ContentView__
#define __Engine__ContentView__
#include "Engine.h"
#include "GLView.h"



class ContentView : public GLView {
public:
    ContentView(ZDB * a_zdb, GLViews * content_views = 0);
    ~ContentView();
    
    GLView * content = 0;
    float border_width = 2;

    void addSubview(GLView * a_view, bool strong = false);
    
    void drawScene(double duration, double boo);
    float vertical_gap = 0;
    
};

#endif /* defined(__Engine__ContentView__) */
