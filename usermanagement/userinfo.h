#ifndef USERINFO_H
#define USERINFO_H
#include<QObject>
#include<QString>
#include <QStringList>

class UserInfo : public QObject
{
private:
    UserInfo();
    static UserInfo* pUserInfo;
public:
    static UserInfo* GetInstance();
    static void FreeSpace();
    QString UserID;         //用户编号
    QString User_Name;      //用户名
    QString Role_ID;        //角色编号
    QString Role_Name;      //角色名
    QStringList PermissionIDList; //角色权限ID列表
};

#endif // USERINFO_H
