#include "usermanagementview.h"

UserManagementView::UserManagementView(QWidget *parent) : QWidget(parent)
{
    Creat_UserManageView();
    Creat_TabViewMenu();
    addUser_View = new AddUserView(this);
    alterUserInfo_View = new AlterUserInfoDialog(this);
    alterUserRole_View = new AlterUserRoleDialog(this);

    connect(AddUser_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserAddView()));
    //弹出菜单槽函数
    connect(userTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_TabViewMenu(QPoint)));
}
UserManagementView::~UserManagementView(){

}
void UserManagementView::Creat_TabViewMenu(){

    popMenu = new QMenu(userTableView);
    QAction *deleteUser = new QAction("删除");
    QAction *alterUserInfo = new QAction("信息修改");
    QAction *alterUserRole= new QAction("角色修改");
    popMenu->addAction(alterUserInfo);
    popMenu->addAction(alterUserRole);
    popMenu->addAction(deleteUser);

    connect(alterUserInfo,SIGNAL(triggered()),this,SLOT(on_AlterUserInfo()));
    connect(alterUserRole,SIGNAL(triggered()),this,SLOT(on_alterUserRole()));
    connect(deleteUser,SIGNAL(triggered()),this,SLOT(on_deleteUser()));

}
//用户管理界面
void UserManagementView::Creat_UserManageView(){
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
    connect(userSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserSearch()));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(userSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    usertableModel = new QSqlTableModel(this,this->mydb);//绑定数据库
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
    userTableView->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单

    QVBoxLayout *layoutv= new QVBoxLayout; //垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(userTableView);

    this->setLayout(layoutv);

}

//查询
void UserManagementView::on_UserSearch(){
    QString userID =  QString("USER_ID like '%%1%'").arg(userID_Edit->text());
    QString userName =  QString("USER_NAME like '%%1%'").arg(userName_Edit->text());
    QString realName =  QString("REAL_NAME like '%%1%'").arg(realName_Edit->text());
    QString filterStr = "";

    if(!userID_Edit->text().isEmpty())
        filterStr.append(userID);
    if(!userName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(userName);
    }

    if(!realName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(realName);
    }

    usertableModel->setFilter(filterStr); //数据库模型查询 过滤器
    usertableModel->select();
}
//右键菜单响应函数
void UserManagementView::on_TabViewMenu(QPoint pos){
     QModelIndex index = userTableView->indexAt(pos);
#if 1
     if (index.isValid())
     {
         popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
     }
#endif
}

//修改用户基本信息
void UserManagementView::on_AlterUserInfo(){
    //获取当前选择行的用户信息
    QStringList UserInfoList;
    int row = userTableView->currentIndex().row();
    qDebug()<< row;
    int i;
    for(i = 0; i < 7; i++)
    {
        //遍历第row行的所有信息
        QModelIndex index = usertableModel->index(row,i);
        QString name = usertableModel->data(index).toString();
        qDebug()<<name<<" ";
        UserInfoList<<name;
    }
    alterUserInfo_View->userID_Edit->setText(UserInfoList.at(0));
    alterUserInfo_View->userID_Edit->setReadOnly(true);
    alterUserInfo_View->userName_Edit->setText(UserInfoList.at(1));
    alterUserInfo_View->passWorld_Edit->setText(UserInfoList.at(2));
    alterUserInfo_View->realName_Edit->setText(UserInfoList.at(3));
    alterUserInfo_View->userTel_Edit->setText(UserInfoList.at(4));
    alterUserInfo_View->userEmail_Edit->setText(UserInfoList.at(5));
    alterUserInfo_View->userDec_Edit->setText(UserInfoList.at(6));
    alterUserInfo_View->show();

    //插入数据库功能后续实现
}

//修改用户角色
void UserManagementView::on_alterUserRole(){
    alterUserRole_View->show();
}

//删除用户
void UserManagementView::on_deleteUser(){

}

//新增用户
void UserManagementView::on_UserAddView(){
    addUser_View->show();
    //插入数据库功能后续实现
    //connect(addUser_View->addUser_PB,SIGNAL(clicked(bool)),this,SLOT(on_UserAddView()));
}
/*数据库连接*/
void UserManagementView::MysqlConnect(){
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
