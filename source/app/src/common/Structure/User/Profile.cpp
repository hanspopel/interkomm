//
//  User.cpp
//  intercom_ios
//
//  Created by Sascha Arlt on 07.09.20.
//

#include "Profile.h"
#include "Interkomm.h"


Profile::Profile(ZDB * a_zdb) : User(a_zdb){
    init();
}

Profile::Profile(ZDB * a_zdb, string a_name) : User(a_zdb, a_name){
    str_inf.profile_name = a_name;
    str_inf.uuid = get_uuid();
    init();
}

void Profile::init(){
    
}

Profile * Profile::load_profile(ZDB * a_zdb){
    
    
    string path = "/Profile/profile.profile";
    unsigned long length = 0;
    void * content = loadDataAtPath(path, &length);
    
    if (content) {
        mss * session = new mss((char*)content, (int)length);
        
        string profile_name = session->read_string();
        string profile_display_name = session->read_string();
        string profile_display_tag = session->read_string();
        string profile_uuid = session->read_string();

        Profile * a_profile = new Profile(a_zdb,profile_name);
        a_profile->str_inf.display_name = profile_display_name;
        a_profile->str_inf.display_tag = profile_display_tag;
        a_profile->str_inf.uuid = profile_uuid;
        a_profile->str_inf.profile_name = profile_name;

        
        delete session;

        if (a_profile) {
            return a_profile;
        }

    }
    
    Profile * a_profile = new Profile(a_zdb,"MaxMusterFrau");
    a_profile->just_created = true;
    Profile::save_profile(a_profile, a_zdb);
    
    return a_profile;

}

bool Profile::save_profile(Profile * a_profile, ZDB * a_zdb){
    
    if (a_zdb->gl->in_background->value()) {
        return false;
    }
    
    mss * session = new mss(0001);
    session->write_string(a_profile->_name());
    session->write_string(a_profile->str_inf.display_name);
    session->write_string(a_profile->str_inf.display_tag);
    session->write_string(a_profile->str_inf.uuid);
    
    a_zdb->dispatch->on_default([=]{
        writeDataWithLengthToPath("/Profile/profile.profile", session->session_content, session->write_offset);
        delete session;
    });
    
    return true;

}


