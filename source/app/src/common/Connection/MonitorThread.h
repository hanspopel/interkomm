//
//  ConnectionManager.h
//  touchAble Pro
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//


#ifndef __Engine__MonitorCallback__
#define __Engine__MonitorCallback__

#include "Thread.h"
#include "Engine.h"



class MonitorThread :
	public CThread {
public:
        MonitorThread(Callback * mon_callback);
        ~MonitorThread();

        Callback * monitor_callback = 0;
        
	bool Work();
};

#endif /* defined(__Engine__MonitorCallback__) */
