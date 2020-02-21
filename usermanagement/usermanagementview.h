#ifndef USERMANAGEMENTVIEW_H
#define USERMANAGEMENTVIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QToolBar>
#include <QGuiApplication>
#include <QLayout>
#include <QRect>
#include <QScreen>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QFrame>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QDateEdit>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QModelIndex>

#include "userinfo.h"
#include "logmodel.h"
#include "adduserview.h"
#include "alteruserinfodialog.h"
#include "alteruserroledialog.h"


class UserManagementView : public QWidget
{
    Q_OBJECT
public:
    UserManagementView(QWidget *parent = nullptr);
    ~UserManagementView();

    UserInfo *pUser;
    LogModel *pLog;
    QMap<QString,QString> roleMap;
    //用户界面控件
    QTableView *userTableView;      //用户信息显示表格
    QPushButton *AddUser_pB;        //新增用户

    QLineEdit *userName_Edit;       //用户名
    QLineEdit *userID_Edit;         //员工编号
    QLineEdit *realName_Edit;       //真实姓名

    QPushButton *outUser_PB;        //用户数据导出
    QPushButton *batchInputUser_PB; //用户信息批量导入

    QMenu *popMenu; //菜单
    //界面
    AddUserView* addUser_View;
    AlterUserInfoDialog* alterUserInfo_View;
    AlterUserRoleDialog* alterUserRole_View;
    //数据库相关
    QSqlTableModel* usertableModel;
    QSqlDatabase mydb;

    void Creat_UserManageView();    //用户管理界面
    void Creat_TabViewMenu();       //右击选项单
signals:

public slots:
    void on_UserSearch();
    void on_UserAddView();
    void on_InsertUserInfoDb();
    void on_AlterUserInfoDb();

    void on_TabViewMenu(QPoint pos);    //右键菜单响应函数
    void on_AlterUserInfo();
    void on_alterUserRole();
    void on_deleteUser();
};

#endif // USERMANAGEMENTVIEW_H
