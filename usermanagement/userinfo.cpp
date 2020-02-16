#include "userinfo.h"

UserInfo* UserInfo::pUserInfo = NULL;
UserInfo::UserInfo()
{

}

UserInfo* UserInfo::GetInstance(){
    if(pUserInfo == NULL){
        pUserInfo = new UserInfo;
    }
    return pUserInfo;
}

void UserInfo::FreeSpace(){
    if(pUserInfo != NULL){
        delete pUserInfo;
    }
}
