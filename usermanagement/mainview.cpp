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
    //UserInfo::FreeSpace();
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

    login_Action = new QAction("登录", this);//新建登录动作
    toolBar->addAction(login_Action);
    toolBar->setMovable(false);// 设置工具栏不可移动

    LoginView = new LoginDialog(this);
    connect(login_Action,&QAction::triggered,LoginView,&QDialog::show);
    connect(LoginView,SIGNAL(LoginSignal()),this,SLOT(on_LoginSuccess()));
}

//多界面切换控制器
void MainView::CreatStackWidget(){
    stackWidget = new QStackedWidget;
    //QWidget *user_manager = Creat_UserManageView();//用户管理界面
    //QWidget *user_log = Creat_UserLogView();//用户日志界面
    //QWidget *role_permissions = Creat_RolePermissionsView(); //角色权限管理界面
    user_log = new UserLogView(this);
    user_manager = new UserManagementView(this);
    role_permissions = new RolePermissionsView(this);
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
    if(action->text()=="用户日志"){
        user_log->logtableModel->submitAll();
        stackWidget->setCurrentIndex(2);
    }

}
//更改登录按钮
void MainView::on_LoginSuccess(){
    QString loginText;
    loginText.append(LoginView->pUser->User_Name);
    loginText.append("/切换");
    login_Action->setText(loginText);
}


