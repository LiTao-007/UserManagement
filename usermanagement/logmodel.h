#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QObject>
#include <QDateTime>
#include "sys_mysqlmodel.h"

//日志等级
#define FATAL 1;  //致命
#define ERROR 2;  //错误
#define WARN  3;  //告警
#define INFO  4;  //一般信息

class LogModel : public QObject
{
private:
    LogModel();
    static LogModel* Log;
public:
    Sys_MySQLModel* pDb;
    static LogModel* GetInstance();
    //用户操作日志导入
    bool InsertUserLogDb(QString UserID,int LogLevl,int PermissionsID,int Result,QString LogContent);
    //系统日志导入
    bool InsertSysLogDb(QString UserID,int LogLevl,QString LogContent);
    //系统日志导出文档
    bool OutSysLogToWorld(QString UserID,int LogLevl,QString LogContent);
    //用户操作日志导出文档
    bool OutUserLogToWorld(QString UserID,int LogLevl,
                           int PermissionsID,bool Result,QString LogContent);
signals:

public slots:
};


#endif // LOGMODEL_H
