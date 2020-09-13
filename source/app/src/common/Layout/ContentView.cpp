//
//  ContentView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ContentView.h"

//constructor
ContentView::ContentView(ZDB * a_zdb, GLViews * content_views) : GLView(a_zdb) {
    
    if (content_views) {
        content_views->push_back(this);
    }
    border_width = 4;
    content = new GLView(zdb);
    content->round_corners = true;
    content->setUniformSpacing(border_width);
    GLView::addSubview(content);
    
}

//deconstructor
ContentView::~ContentView() {
    
}

void ContentView::addSubview(GLView * a_view, bool strong){
    //a_view->setUniformSpacing(1);
    content->addSubview(a_view, strong);
}

void ContentView::drawScene(double duration, double boo){
    
    colorGL = MMBarColor();
    
    
    GLDrawRect(CRectMake(0, vertical_gap, vertical_gap, frame.size.height - vertical_gap));
    GLDrawRect(CRectMake(frame.size.width - vertical_gap, vertical_gap, vertical_gap, frame.size.height - vertical_gap));
    GLDrawRect(CRectMake(vertical_gap, frame.size.height - vertical_gap, frame.size.width - 2 * border_width, vertical_gap));

}


