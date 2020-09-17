////////////////////////////////////////////////////////////////////////////
//  Project: touchAble server
//  Date: 18.06.2014
//  Author: Mikhail Burilov (http://itserviceplus.net)
//  Copyright: (c) 2014
//
//  ClientMonitorThread
//  Thread class to monitor clients and script in Ableton
////////////////////////////////////////////////////////////////////////////

#include "MonitorThread.h"

MonitorThread::MonitorThread(Callback * mon_callback) {
    
    monitor_callback = mon_callback;
    
}


MonitorThread::~MonitorThread() {
}

bool MonitorThread::Work() {
	while (running) {

        monitor_callback->call(0);
		
        usleep(1000 * 3000);

	}
    return true;
}
