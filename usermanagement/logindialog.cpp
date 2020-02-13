#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("登录/注册"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体

    resize(180,180);
    MysqlConnect();
    //用户信息初始化
    User.name = "登录/注册";
    User.permissionID = "1";

    nameLabel = new QLabel("用户名");
    passwordLabel = new QLabel("密码");
    name_Edit = new QLineEdit;
    password_Edit = new QLineEdit;
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

    qDebug()<< "登录成功 隐藏该界面 跳转至主界面";
    //this->name_Edit->clear();
    this->password_Edit->clear();
    this->close();
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


