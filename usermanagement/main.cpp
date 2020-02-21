#include "mainview.h"
#include "sys_mysqlmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("windows"); //设置界面风格为window风格
    Sys_MySQLModel* pDb = Sys_MySQLModel::GetInstance();
    pDb->MySQLInit("QMYSQL","192.168.8.153","smartwave_db","root","lonsin");
    pDb->MySQLConnect();
    MainView w;
    w.show();

    return a.exec();
}
