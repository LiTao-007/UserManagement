#include "sys_mysqlmodel.h"

Sys_MySQLModel* Sys_MySQLModel::MysqlConnect = NULL;

Sys_MySQLModel::Sys_MySQLModel()
{

}

/****************************************************************************
函数名称: GetInstance
函数功能: 获取数据库单例对象
输入: 无
输出: 无
返回值: 无
特殊说明:
 ****************************************************************************/
Sys_MySQLModel* Sys_MySQLModel::GetInstance(){
    if(MysqlConnect == NULL){
        MysqlConnect = new Sys_MySQLModel;
    }
    return MysqlConnect;
}

/****************************************************************************
函数名称: MySQLInit
函数功能: 数据连接信息获取
输入:
     DbType:连接的数据库类型
     HostName:ip地址
     DbName:连接数据库名
     UserName:数据库用户名
     Password:密码
输出: 无
返回值: 无
特殊说明:
 ****************************************************************************/
void Sys_MySQLModel::MySQLInit(const QString DbType,
                       const QString HostName,const QString DbName,
                       const QString UserName,const QString Password){
    MySQLInfo.DbType = DbType;
    MySQLInfo.HostName = HostName;
    MySQLInfo.DbName = DbName;
    MySQLInfo.UserName = UserName;
    MySQLInfo.Password = Password;
}
/****************************************************************************
函数名称: MySQLConnect
函数功能: 数据库连接
输入: 无
输出: 无
返回值: 无
特殊说明:
 ****************************************************************************/
void Sys_MySQLModel::MySQLConnect(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        myDb = QSqlDatabase::addDatabase(MySQLInfo.DbType);
        myDb.setHostName(MySQLInfo.HostName);
        myDb.setDatabaseName(MySQLInfo.DbName);
        myDb.setUserName(MySQLInfo.UserName);
        myDb.setPassword(MySQLInfo.Password); //数据库密码lonsin
    }
    if(!myDb.open())
    {
        qDebug()<<"数据库连接失败："<<myDb.lastError().text();
        //QMessageBox::warning(MysqlConnect,"错误",myDb.lastError().text());
    }
    qDebug()<<"数据库连接成功";
    return;
}

