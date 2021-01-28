//
//  Server.cpp
//  MyMon
//
//  Created by Christian Blomert on 11/10/16.
//  Copyright © 2016 Christian Blomert. All rights reserved.
//

#include "MCGroupSendReceive.h"


// bei Auswahl Channel soll an MCGroup gesendet werden.

MCGroupSend::MCGroupSend(){

    mcgroupAddress = "224.1.50.15";

    sock = socket(AF_INET,SOCK_DGRAM,NULL);
    // zuerst alles auf 0 setzen
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET; // Adress Familie
    addr.sin_port = htons(MCGROUPPORT); // Port-Nummer
    addr.sin_addr.s_addr = inet_addr(mcgroupAddress); // host
    

    MCSend();

}


void MCGroupSend::MCSend(){
    

    sendto( sock, "test", 5, 0, (sockaddr*)&addr, sizeof addr);
//    rc = recvfrom( sock, buffer, sizeof buffer, 0, 0, 0);
//        if( rc > 0 ) {
//            printf("%s\\n", buffer);
//
//        }
//        else printf(".");
//    sleep( 5 );


}
