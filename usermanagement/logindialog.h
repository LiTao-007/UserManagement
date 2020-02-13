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

typedef struct User_info {  //登录用户信息
    QString nameID;         //用户编号
    QString name;           //用户名
    QString permissionID;   //权限
}UserInfo;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void MysqlConnect();

    UserInfo User;

    bool flag; //用户切换标志
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

};

#endif // LOGINDIALOG_H
