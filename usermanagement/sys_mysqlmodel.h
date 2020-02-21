#ifndef SYS_MYSQLMODEL_H
#define SYS_MYSQLMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

//数据库连接信息存储
typedef struct DbInfo
{
    QString DbType;
    QString HostName;
    QString DbName;
    QString UserName;
    QString Password;
}DbConnectInfo;

class Sys_MySQLModel : public QObject
{
    Q_OBJECT
private:
    Sys_MySQLModel();
    static Sys_MySQLModel* MysqlConnect;
public:
    DbConnectInfo MySQLInfo;
    QSqlDatabase myDb;
    static Sys_MySQLModel* GetInstance();
    //获取数据库连接信息
    void MySQLInit(const QString DbType,const QString HostName,const QString DbName,const QString UserName,const QString Password);
    //数据库建立连接
    void MySQLConnect();

signals:

public slots:
};

#endif // SYS_MYSQLMODEL_H
