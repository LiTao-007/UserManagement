#include "logmodel.h"


LogModel* LogModel::Log = NULL;
LogModel::LogModel()
{
    pDb = Sys_MySQLModel::GetInstance();
}
/****************************************************************************
函数名称: GetInstance
函数功能: 获取日志单例对象
输入: 无
输出: 无
返回值: 无
特殊说明:
 ****************************************************************************/
LogModel* LogModel::GetInstance(){
    if(Log == NULL){
        Log = new LogModel;
    }
    return Log;
}

/****************************************************************************
函数名称: InsertUserLogDb
函数功能: 用户操作日志插入数据库
输入:
    UserID:         当前登录用户
    LogLevl:        日志等级
    PermissionsID:  操作权限ID
    Result:         操作结果
    LogContent:     事件描述
输出: 数据插入数据库表 tb_log_operator
返回值: 插入数据是否成功 bool
特殊说明:
 ****************************************************************************/
bool LogModel::InsertUserLogDb(QString UserID,int LogLevl,
                               int PermissionsID,int Result,QString LogContent){
    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳
    //组合Sql语句
    QString userLogSql = "INSERT INTO tb_log_operator"
                         "(LOG_TIME,PERMISSION_ID,LOG_RESULT,LOG_LEVEL,USER_ID,DESCR)"
                         "VALUES(";
    userLogSql += QString::number(timeT)+","+QString::number(PermissionsID)+",";
    userLogSql += QString::number(Result)+","+QString::number(LogLevl)+",";
    userLogSql += UserID+",'"+LogContent+"')";
    qDebug()<<__FUNCTION__<<userLogSql;
    //执行Sql语句

    QSqlQuery query(Log->pDb->myDb);
    if(!query.exec(userLogSql)){
       qDebug()<<__FUNCTION__<<query.lastError().text();
       return false;
    }
    return true;

}
/****************************************************************************
函数名称: InsertSysLogDb
函数功能: 系统日志插入数据库
输入:
    UserID:     当前登录用户
    LogLevl:    日志等级
    LogContent: 事件描述
输出: 数据插入数据库表 tb_log_system
返回值: 插入数据是否成功 bool
特殊说明:
 ****************************************************************************/
bool LogModel::InsertSysLogDb(QString UserID,int LogLevl,QString LogContent){
    return true;
}
/****************************************************************************
函数名称: OutSysLogToWorld
函数功能: 系统日志导出
输入:
    UserID:         当前登录用户
    LogLevl:        日志等级
    PermissionsID:  操作权限ID
    Result:         操作结果
    LogContent:     事件描述
输出: 指定的路径的日志文档
返回值: 导出是否成功 bool
特殊说明:
 ****************************************************************************/
bool LogModel::OutSysLogToWorld(QString UserID,int LogLevl,QString LogContent){
    return true;
}
/****************************************************************************
函数名称: InsertSysLogDb
函数功能: 系统日志插入数据库
输入:
    UserID:         当前登录用户
    LogLevl:        日志等级
    PermissionsID:  操作权限ID
    Result:         操作结果
    LogContent:     事件描述
输出: 指定的路径的日志文档
返回值: 导出是否成功 bool
特殊说明:
 ****************************************************************************/
bool OutUserLogToWorld(QString UserID,int LogLevl,
                       int PermissionsID,bool Result,QString LogContent){
    return true;
}

