#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "userinfo.h"
#include "logmodel.h"

typedef struct User_Info
{
    QString UserID;         //用户编号
    QString User_Name;      //用户名
    QString Role_ID;        //角色编号
    QString Role_Name;      //角色名
    QStringList PermissionIDList; //角色权限ID列表
}User;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void MysqlConnect();

    //User* pUser;
    UserInfo* pUser;
    LogModel* pLog;


    QLabel *nameLabel;
    QLabel *passwordLabel;
    QLineEdit *name_Edit;
    QLineEdit *password_Edit;
    QPushButton *login_PB;
    QPushButton *cancel_PB;

private:
    QSqlDatabase login_db;

private slots:
    void on_Login();
    void on_Cancel();

signals:
    void LoginSignal();

};

#endif // LOGINDIALOG_H
