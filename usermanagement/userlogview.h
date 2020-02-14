#ifndef USERLOGVIEW_H
#define USERLOGVIEW_H

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

class UserLogView : public QWidget
{
    Q_OBJECT
public:
    UserLogView(QWidget *parent = nullptr);
    ~UserLogView();

    QTableView *logTableView;      //用户日志
    QLineEdit *logUserName_Edit;     //用户名
    QLineEdit *logPermissionDef_Edit; //操作类型（权限）
    QComboBox *logLevel_Edit; // 操作等级
    QDateEdit *logStartDate_Edit;   //时间
    QDateEdit *logEndDate_Edit;

    QSqlTableModel* logtableModel;
    QSqlDatabase mydb;
    void MysqlConnect();        //数据库连接
    void Creat_UserLogView();

signals:

public slots:
    void on_UserLogSearch();    //日志信息查询
};

#endif // USERLOGVIEW_H
