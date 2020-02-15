#ifndef ROLEPERMISSIONSVIEW_H
#define ROLEPERMISSIONSVIEW_H

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

#include "addpermissionsdialog.h"
#include "addroledialog.h"
#include "alterroleinfodialog.h"
#include "alterrolepmsdialog.h"

class RolePermissionsView : public QWidget
{
    Q_OBJECT
public:
    RolePermissionsView(QWidget *parent = nullptr);
    ~RolePermissionsView();

    AddPermissionsDialog* AddPermissions_View;
    AddRoleDialog* AddRole_View;
    AlterRoleInfoDialog* AlterRoleInfo_View;
    AlterRolePMSDialog* AlterRolePMS_View;
    //角色权限界面控件
    QTableView  *roleTableView;      //角色信息显示表格
    QPushButton *AddRole_pB;         //新增角色
    QPushButton *AddPermissions_pB;  //新增权限

    QLineEdit *roleName_Edit;       //角色名
    QLineEdit *roleDEC_Edit;        //角色描述

    QMenu *popMenu; //菜单

    QSqlTableModel* roletableModel;
    QSqlDatabase mydb;

    void MysqlConnect();        //数据库连接

    void Creat_RolePermissionsView();
    void Creat_TabViewMenu(); //右击选项单
signals:

public slots:
    void on_RoleSearch(); //查询
    void on_RoleAddView(); //新增角色
    void on_PermissionsAddView(); //新增权限

    void on_TabViewMenu(QPoint pos); //右键菜单响应函数
    void on_AlterRoleInfo();
    void on_alterPermissions();
    void on_deleteRole();
};

#endif // ROLEPERMISSIONSVIEW_H
