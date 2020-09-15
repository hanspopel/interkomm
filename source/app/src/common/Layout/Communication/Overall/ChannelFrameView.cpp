//
//  ChannelFrameView.cpp
//  MyMon
//
//  Created by pascal kaap on 19/01/19.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "ChannelFrameView.h"



ChannelFrameView::ChannelFrameView(ZDB * a_zdb, Channel * a_channel) : GLView(a_zdb) {
    
    channel = a_channel;
    
    main_grid = new GLGridView(a_zdb,CRectMake(0, 0, 1, 1));

    main_grid->setGridSize(SizeMake(1, grid_size_y));
    main_grid->spacingY = 0;
    main_grid->spacingTop = 0;
    main_grid->spacingBottom = 0;
    main_grid->spacing_top = 0;
    main_grid->spacing_bottom = 0;
//    main_grid->backgroundColor = GLTRed();
    addSubview(main_grid);

    
    
}

ChannelFrameView::~ChannelFrameView(){
    delete main_grid;
}
