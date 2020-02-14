#include "mainview.h"

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("用户管理模块");
#if 0  //全屏
    QList<QScreen *> list_screen = QGuiApplication::screens();
    resize(list_screen.at(0)->geometry().size());
#endif
    resize(600,350);
    CreatTool();
    CreatStackWidget();

    //槽函数
    //界面切换bind
    connect(user_log_Action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(role_permissions_Action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(user_manager_Action,&QAction::triggered,this,&MainView::on_SwitchPage);

}

MainView::~MainView()
{

}

//工具栏
void MainView::CreatTool(){
    QToolBar *toolBar = addToolBar("工具栏");//添加登录工具条
    user_log_Action = new QAction("用户日志",this);
    role_permissions_Action = new QAction("角色权限管理",this);
    user_manager_Action = new QAction("用户管理",this);
    QWidget *spacer = new QWidget(this);
    toolBar->addAction(user_manager_Action);
    toolBar->addSeparator();
    toolBar->addAction(role_permissions_Action);
    toolBar->addSeparator();
    toolBar->addAction(user_log_Action);

    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //填充空白
    toolBar->addWidget(spacer);

    login_Action = new QAction("登录/注册", this);//新建登录动作
    toolBar->addAction(login_Action);
    toolBar->setMovable(false);// 设置工具栏不可移动

    LoginView = new LoginDialog(this);
    connect(login_Action,&QAction::triggered,LoginView,&QDialog::show);
}

//角色权限管理界面
QWidget* MainView::Creat_RolePermissionsView(){

    QWidget *userPage = new QWidget;
    QLabel *titleLabel = new QLabel("角色权限管理界面");

    QVBoxLayout *layoutv= new QVBoxLayout; //垂直布局
    layoutv->addWidget(titleLabel);
    userPage->setLayout(layoutv);
    return userPage;
}

//多界面切换控制器
void MainView::CreatStackWidget(){
    stackWidget = new QStackedWidget;
    //QWidget *user_manager = Creat_UserManageView();//用户管理界面
    //QWidget *user_log = Creat_UserLogView();//用户日志界面
    QWidget *role_permissions = Creat_RolePermissionsView(); //角色权限管理界面
    user_log = new UserLogView(this);
    user_manager = new UserManagementView(this);
    stackWidget->addWidget(user_manager);
    stackWidget->addWidget(role_permissions);
    stackWidget->addWidget(user_log);

    setCentralWidget(stackWidget);
}

//槽函数
//功能界面切换
void MainView::on_SwitchPage(){
    QAction *action = qobject_cast<QAction *>(sender());//获取发送者对象
    if(action->text()=="用户管理")
        stackWidget->setCurrentIndex(0);
    if(action->text()=="角色权限管理")
        stackWidget->setCurrentIndex(1);
    if(action->text()=="用户日志")
        stackWidget->setCurrentIndex(2);

}

/*数据库连接*/
void MainView::MysqlConnect(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        mydb = QSqlDatabase::addDatabase("QMYSQL");
    }
    mydb.setHostName("192.168.8.153");
    mydb.setDatabaseName("smartwave_db");
    mydb.setPassword("lonsin");
    mydb.setUserName("root");

    if(!mydb.open())
    {
        QMessageBox::warning(this,"错误",mydb.lastError().text());
    }
    return;
}
