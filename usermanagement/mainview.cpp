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
//用户管理界面
QWidget* MainView::Creat_UserManageView(){
    QWidget *userPage = new QWidget;
    QLabel *titleLabel = new QLabel("用户信息管理");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    AddUser_pB = new QPushButton("新增用户");

    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(AddUser_pB);

    //查询部分
    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel * user_ID = new QLabel("员工编号");
    userID_Edit  = new QLineEdit();
    QLabel * user_Name = new QLabel("用户名称");
    userName_Edit = new QLineEdit();
    QLabel * real_Name = new QLabel("真实名称");
    realName_Edit = new QLineEdit();
    layout2->addWidget(user_ID);
    layout2->addWidget(userID_Edit);
    layout2->addStretch();
    layout2->addWidget(user_Name);
    layout2->addWidget(userName_Edit);
    layout2->addStretch();
    layout2->addWidget(real_Name);
    layout2->addWidget(realName_Edit);

    QPushButton *userSearch_pB = new QPushButton("查询");
    //connect(userSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserSearch()));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(userSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    usertableModel = new QSqlTableModel(userPage,this->mydb);//绑定数据库
    usertableModel->setTable("tb_user_rec");
    usertableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    usertableModel->insertColumn(2);
    usertableModel->setHeaderData(0,Qt::Horizontal,"用户编号");
    usertableModel->setHeaderData(1,Qt::Horizontal,"用户名称");
    usertableModel->setHeaderData(2,Qt::Horizontal,"密码");
    usertableModel->setHeaderData(3,Qt::Horizontal,"真实姓名");
    usertableModel->setHeaderData(4,Qt::Horizontal,"手机号");
    usertableModel->setHeaderData(5,Qt::Horizontal,"邮箱");
    usertableModel->setHeaderData(6,Qt::Horizontal,"备注");
    usertableModel->select(); //选取整个表的所有行

    userTableView = new QTableView(this);
    userTableView->setModel(usertableModel);
    userTableView->setColumnHidden(2,true);
    //userTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动适应窗口大小
    userTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    //userTableView->verticalHeader()->setVisible(false);//隐藏列表头
    userTableView->horizontalHeader()->setHighlightSections(false); //取消表头的在选中单元格时的高亮状态
    userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑
    userTableView->setSelectionMode(QAbstractItemView::SingleSelection); //只选择一行

    QVBoxLayout *layoutv= new QVBoxLayout; //垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(userTableView);


    userPage->setLayout(layoutv);
    return userPage;
}
//用户日志界面
QWidget* MainView::Creat_UserLogView(){
    QWidget *logPage = new QWidget;
    QLabel *titleLabel = new QLabel("用户日志");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);

    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    layout1->addWidget(titleLabel);
    layout1->addStretch();

    //查询部分
    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel * user_Name = new QLabel("用户名称");
    logUserName_Edit = new QLineEdit();
    QLabel * logPermissionDef = new QLabel("权限描述");
    logPermissionDef_Edit = new QLineEdit();
    QLabel * logLevel = new QLabel("事件等级");
    logLevel_Edit = new QComboBox(this);
    logLevel_Edit->addItem("无");
    QLabel *log_Time    = new QLabel("日志时间");
    logStartDate_Edit   = new QDateEdit();
    QLabel *To   = new QLabel("至");
    logEndDate_Edit     = new QDateEdit(QDate::currentDate()); //日历 并显示当前时间
    logStartDate_Edit->setCalendarPopup(true);
    logEndDate_Edit->setCalendarPopup(true);

    layout2->addWidget(user_Name);
    layout2->addWidget(logUserName_Edit);
    layout2->addStretch();
    layout2->addWidget(logPermissionDef);
    layout2->addWidget(logPermissionDef_Edit);
    layout2->addStretch();
    layout2->addWidget(logLevel);
    layout2->addWidget(logLevel_Edit);
    layout2->addStretch();
    layout2->addStretch();

    QPushButton *logSearch_pB = new QPushButton("查询");
    //connect(userSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserSearch()));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(log_Time);
    layout3->addWidget(logStartDate_Edit);
    layout3->addWidget(To);
    layout3->addWidget(logEndDate_Edit);
    layout3->addStretch();
    layout3->addWidget(logSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    //表格
    logtableModel = new QSqlTableModel(logPage,this->mydb);//绑定数据库
    logtableModel->setTable("tb_log_operator");
    logtableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    logtableModel->insertColumn(2);
    logtableModel->setHeaderData(0,Qt::Horizontal,"序号");
    logtableModel->setHeaderData(1,Qt::Horizontal,"日志时间");
    logtableModel->setHeaderData(2,Qt::Horizontal,"权限描述");
    logtableModel->setHeaderData(3,Qt::Horizontal,"操作结果");
    logtableModel->setHeaderData(4,Qt::Horizontal,"事件等级");
    logtableModel->setHeaderData(5,Qt::Horizontal,"操作用户");
    logtableModel->setHeaderData(6,Qt::Horizontal,"操作描述");
    logtableModel->select(); //选取整个表的所有行

    logTableView = new QTableView(this);
    logTableView->setModel(logtableModel);
    //logTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动适应窗口大小
    logTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    //logTableView->verticalHeader()->setVisible(false);//隐藏列表头
    logTableView->horizontalHeader()->setHighlightSections(false); //取消表头的在选中单元格时的高亮状态
    logTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑
    logTableView->setSelectionMode(QAbstractItemView::SingleSelection); //只选择一行

    QVBoxLayout *layoutv= new QVBoxLayout; //垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(logTableView);

    logPage->setLayout(layoutv);
    return logPage;
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
    QWidget *user_manager = Creat_UserManageView();//用户管理界面
    QWidget *user_log = Creat_UserLogView();//用户日志界面
    QWidget *role_permissions = Creat_RolePermissionsView(); //角色权限管理界面

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
