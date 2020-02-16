#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("登录/注册"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    pUser = UserInfo::GetInstance();
    resize(200,180);
    MysqlConnect();
    //用户信息初始化
    nameLabel = new QLabel("用户名");
    passwordLabel = new QLabel("密码");
    name_Edit = new QLineEdit(this);
    password_Edit = new QLineEdit(this);
    login_PB = new QPushButton("登录");
    cancel_PB = new QPushButton("取消");

    password_Edit->setEchoMode(QLineEdit::Password);//密码显示星号

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(nameLabel,0,0);
    gridLayout->addWidget(name_Edit,0,1);
    gridLayout->addWidget(passwordLabel,1,0);
    gridLayout->addWidget(password_Edit,1,1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(login_PB);
    hLayout->addStretch();
    hLayout->addWidget(cancel_PB);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addLayout(hLayout);

    connect(login_PB,SIGNAL(clicked(bool)),this,SLOT(on_Login()));
    connect(cancel_PB,SIGNAL(clicked(bool)),this,SLOT(on_Cancel()));
    setLayout(vLayout);
}

LoginDialog::~LoginDialog(){
    delete pUser;
}

/*
登录槽函数
*/
void LoginDialog::on_Login(){
    if(name_Edit->text().isEmpty()||password_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","请输入用户民和密码");
        return;
    }

    QSqlQuery query(this->login_db);
    QString sql = "select USER_ID,`USER_NAME`,`Password` from tb_user_rec where `USER_NAME`='"+name_Edit->text()+"' and `PASSWORD`='";
    sql +=password_Edit->text()+"'";

    qDebug()<<"执行查询登录用户sql语句："<< sql;

    query.exec(sql);
    qDebug()<<"查询结果数据行数"<<query.numRowsAffected();
    if(query.numRowsAffected()<=0)
    {
        QMessageBox::warning(this,"warning","请正确输入用户或密码");
        return;
    }
    //获取登录用户相关信息
    //获取用户ID、用户名称
    pUser->PermissionIDList.clear();
    while (query.next()) {
        pUser->UserID = query.value(0).toString();
        pUser->User_Name = query.value(1).toString();
    }

    //获取用户角色ID 名称
    QString  Role_sql1 = "select USER_ID,ROLE_ID from tb_user_owned_role_rec where USER_ID = "+pUser->UserID;
    query.exec(Role_sql1);
    while (query.next()) {
        pUser->Role_ID = query.value(1).toString();
    }

    QString  Role_sql2 = "select ROLE_ID,ROLE_NAME,DESCR from tb_user_role_def where ROLE_ID = "+pUser->Role_ID;
    query.exec(Role_sql2);
    while (query.next()) {
        pUser->Role_Name = query.value(1).toString();
    }
    //角色权限id
    QString  Permission_sql = "select ROLE_ID,PERMISSION_ID from tb_user_role_permissions_def where ROLE_ID = "+pUser->Role_ID;
    query.exec(Permission_sql);
    while (query.next()) {
        pUser->PermissionIDList.append(query.value(1).toString());
    }
   //qDebug()<<User.UserID<<" "<< User.User_Name<<" "<<User.Role_ID<<User.Role_Name<<User.PermissionIDList;


    qDebug()<< "登录成功 隐藏该界面 跳转至主界面";
    //this->name_Edit->clear();
    this->password_Edit->clear();
    this->close();
    emit LoginSignal(); //通知登录成功
}

void LoginDialog::on_Cancel(){
    this->close();
}

/*数据库连接*/
void LoginDialog::MysqlConnect(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        login_db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        login_db = QSqlDatabase::addDatabase("QMYSQL");
    }

    login_db.setHostName("192.168.8.153");
    login_db.setDatabaseName("smartwave_db");
    login_db.setPassword("lonsin");
    login_db.setUserName("root");

    if(!login_db.open())
    {
        QMessageBox::warning(this,"错误",login_db.lastError().text());
        //退出登录界面
        this->close(); //关闭登录窗口
    }else{
        qDebug()<<"mysql connect success!!";
    }
}


