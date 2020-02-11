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

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
public:

    QStackedWidget *stackWidget; //堆栈窗体管理，多界面切换

    //工具栏
    QAction *user_manager_Action;
    QAction *role_permissions_Action;
    QAction *user_log_Action;
    QAction *login_Action;

    void CreatTool();           //工具栏操作
    void CreatStackWidget();

    QWidget *Creat_UserManageView();//用户管理界面
    QWidget *Creat_UserLogView();//用户日志界面
    QWidget *Creat_RolePermissionsView(); //角色权限管理界面

private slots:
    void on_SwitchPage();               //功能界面切换
};

#endif // MAINVIEW_H
