#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolBar>
#include <QGuiApplication>
#include <QLayout>
#include <QRect>
#include <QScreen>
#include <QStackedWidget>
#include <QLabel>
#include <QWidget>
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

#include "logindialog.h"
#include "userlogview.h"
#include "usermanagementview.h"
#include "rolepermissionsview.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
public:
    //UserInfo* pUser; //登录用户信息
    QStackedWidget *stackWidget; //堆栈窗体管理，多界面切换

    UserLogView* user_log;
    UserManagementView* user_manager;
    RolePermissionsView* role_permissions;

    //工具栏
    QAction *user_manager_Action;
    QAction *role_permissions_Action;
    QAction *user_log_Action;
    QAction *login_Action;

    //用户界面控件
    QTableView *userTableView;      //用户信息显示表格
    QPushButton *AddUser_pB;        //新增用户
    QPushButton *Permission_pB;     //权限设置
    QLineEdit *userName_Edit;       //用户名
    QLineEdit *userID_Edit;         //员工编号
    QLineEdit *realName_Edit;       //真实姓名

    QPushButton *outUser_PB;        //用户数据导出
    QPushButton *batchInputUser_PB; //用户信息批量导入

    //登录、权限设置和添加界面对象
    LoginDialog  *LoginView;         //登录

    void CreatTool();           //工具栏操作
    void CreatStackWidget();
    //数据库相关
    QSqlTableModel* usertableModel;
    QSqlDatabase mydb;
    void MysqlConnect();        //数据库连接

    QWidget *Creat_UserManageView();    //用户管理界面
    QWidget *Creat_UserLogView();       //用户日志界面
    QWidget *Creat_RolePermissionsView(); //角色权限管理界面

private slots:
    void on_SwitchPage();               //功能界面切换
    void on_LoginSuccess();
};

#endif // MAINVIEW_H
