#include "usermanagementview.h"

UserManagementView::UserManagementView(QWidget *parent) : QWidget(parent)
{
    Creat_UserManageView();
    Creat_TabViewMenu();
    pLog =  LogModel::GetInstance();
    mydb = pLog->pDb->myDb;
    pUser = UserInfo::GetInstance();

    addUser_View = new AddUserView(mydb,this);
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
    //popMenu->addAction(alterUserRole);
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
    alterUserInfo_View->role_Box->clear();
    roleMap.clear();

    QSqlQuery query(this->mydb);
    QString RoleSql = "SELECT ROLE_ID,ROLE_NAME FROM tb_user_role_def";
    query.exec(RoleSql);
    while (query.next()) {
        roleMap.insert(query.value(0).toString(),query.value(1).toString());
    }
    QMap<QString, QString>::const_iterator i;
    for( i=roleMap.constBegin(); i!=roleMap.constEnd(); ++i)
    {
        alterUserInfo_View->role_Box->addItem(i.value()); //添加角色到下拉框
    }

    if(!pUser->PermissionIDList.contains("3")){
        QMessageBox::warning(this,"warning","该用户无修改用户权限!!");
        return;
    }

    //获取当前选择行的用户信息
    QStringList UserInfoList;
    int row = userTableView->currentIndex().row();
    int j;
    for(j = 0; j < 7; j++)
    {
        //遍历第row行的所有信息
        QModelIndex index = usertableModel->index(row,j);
        QString name = usertableModel->data(index).toString();
        UserInfoList<<name;
    }
    QString  Role_sql = "select USER_ID,ROLE_ID from tb_user_owned_role_rec where USER_ID = ";
    Role_sql += UserInfoList.at(0);
    qDebug()<< Role_sql;
    query.exec(Role_sql);
    while (query.next()) {
        UserInfoList<<query.value(1).toString();
    }
    alterUserInfo_View->userID_Edit->setReadOnly(false);
    alterUserInfo_View->userID_Edit->setText(UserInfoList.at(0));
    alterUserInfo_View->userID_Edit->setReadOnly(true);
    alterUserInfo_View->userName_Edit->setText(UserInfoList.at(1));
    alterUserInfo_View->passWorld_Edit->setText(UserInfoList.at(2));
    alterUserInfo_View->realName_Edit->setText(UserInfoList.at(3));
    alterUserInfo_View->userTel_Edit->setText(UserInfoList.at(4));
    alterUserInfo_View->userEmail_Edit->setText(UserInfoList.at(5));
    alterUserInfo_View->userDec_Edit->setText(UserInfoList.at(6));
    alterUserInfo_View->role_Box->setCurrentText(roleMap.value(UserInfoList.at(7)));
    alterUserInfo_View->show();
    //插入数据库功能
    connect(alterUserInfo_View->alterUser_PB,SIGNAL(clicked(bool)),this,SLOT(on_AlterUserInfoDb()));
}
void UserManagementView::on_AlterUserInfoDb(){
    if(alterUserInfo_View->userName_Edit->text().isEmpty()||alterUserInfo_View->passWorld_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","用户名称和密码不能为空!");
        return;
    }
    //相关数据插入对应数据表中
    QSqlQuery query(this->mydb);
    //用户表tb_user_rec
    QString UserSql = "INSERT INTO tb_user_rec VALUE('";
    UserSql += alterUserInfo_View->userID_Edit->text()+"','"+alterUserInfo_View->userName_Edit->text()+"','";
    UserSql += alterUserInfo_View->passWorld_Edit->text()+"','"+alterUserInfo_View->realName_Edit->text()+"','";
    UserSql += alterUserInfo_View->userTel_Edit->text()+"','"+alterUserInfo_View->userEmail_Edit->text()+"','";
    UserSql += alterUserInfo_View->userDec_Edit->toPlainText()+"')";

    //用户角色表tb_user_owned_role_rec
    QString RoleSql = "INSERT INTO tb_user_owned_role_rec VALUE(";
    RoleSql += alterUserInfo_View->userID_Edit->text()+","+roleMap.key(alterUserInfo_View->role_Box->currentText())+")";

    //删除选择的用户信息
    QString delUserSql = "DELETE FROM tb_user_rec WHERE USER_ID = "+alterUserInfo_View->userID_Edit->text();
    QString delRoleSql = "DELETE FROM tb_user_owned_role_rec WHERE USER_ID = "+alterUserInfo_View->userID_Edit->text();

    int choose;
    choose = QMessageBox::question(this, tr("修改用户"),
                                   QString(tr("确认修改该用户")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No)
     {
        return;
     }

    //执行sql语句
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(delUserSql);
    bool ok2 = query.exec(delRoleSql);
    bool ok3 = query.exec(UserSql);
    bool ok4 = query.exec(RoleSql);
    if(ok1&&ok2&&ok3&&ok4)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }
    QMessageBox::information(this,"提示","用户修改成功!!");
    //生成日志
    QString LogDec = "修改用户编号为：" + alterUserInfo_View->userID_Edit->text()+"的用户信息";
    pLog->InsertUserLogDb(pUser->UserID,4,3,1,LogDec);

    alterUserInfo_View->close();
    usertableModel->submitAll();
}
//修改用户角色
void UserManagementView::on_alterUserRole(){
    alterUserRole_View->show();
}

//删除用户
void UserManagementView::on_deleteUser(){
    if(!pUser->PermissionIDList.contains("2")){
        QMessageBox::warning(this,"warning","该用户无新增用户权限!!");
        return;
    }

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
        UserInfoList<<name;
    }
    if(QString::compare(UserInfoList.at(0),pUser->UserID)==0){
        QMessageBox::warning(this,"warning","不能删除自己!!");
        return;
    }
    int choose;
    choose = QMessageBox::question(this, tr("删除用户"),
                                   QString(tr("确认删除该用户")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No)
     {
        return;
     }

    QSqlQuery query(this->mydb);
    //用户表 tb_user_rec 删除选择用户
    QString UserSql = "DELETE FROM tb_user_rec WHERE USER_ID = "+UserInfoList.at(0);
    query.exec(UserSql);
    QString RoleSql = "DELETE FROM tb_user_owned_role_rec WHERE USER_ID = "+UserInfoList.at(0);
    query.exec(RoleSql);
    //生成日志
    QString LogDec = "删除用户:" + UserInfoList.at(1);
    pLog->InsertUserLogDb(pUser->UserID,4,2,1,LogDec);

    usertableModel->submitAll();

}

//新增用户
void UserManagementView::on_UserAddView(){
    addUser_View->role_Box->clear();
    roleMap.clear();
    QSqlQuery query(this->mydb);
    QString RoleSql = "SELECT ROLE_ID,ROLE_NAME FROM tb_user_role_def";
    query.exec(RoleSql);
    while (query.next()) {
        roleMap.insert(query.value(0).toString(),query.value(1).toString());
    }
    QMap<QString, QString>::const_iterator i;
    for( i=roleMap.constBegin(); i!=roleMap.constEnd(); ++i)
    {
        addUser_View->role_Box->addItem(i.value());
    }
    if(pUser->PermissionIDList.contains("1")){
        addUser_View->show();
    }else {
        QMessageBox::warning(this,"warning","该用户无新增用户权限!!");
        return;
    }
    //插入数据库功能后续实现
    connect(addUser_View->addUser_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertUserInfoDb()));
}

void UserManagementView::on_InsertUserInfoDb(){
    if(addUser_View->userID_Edit->text().isEmpty()||addUser_View->userName_Edit->text().isEmpty()
            ||addUser_View->passWorld_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","用户编号、名称和密码不能为空!");
        return;
    }
    //相关数据插入对应数据表中
    QSqlQuery query(this->mydb);
    //用户表tb_user_rec
    QString UserSql = "INSERT INTO tb_user_rec VALUE('";
    UserSql += addUser_View->userID_Edit->text()+"','"+addUser_View->userName_Edit->text()+"','";
    UserSql += addUser_View->passWorld_Edit->text()+"','"+addUser_View->realName_Edit->text()+"','";
    UserSql += addUser_View->userTel_Edit->text()+"','"+addUser_View->userEmail_Edit->text()+"','";
    UserSql += addUser_View->userDec_Edit->toPlainText()+"')";

    //用户角色表tb_user_owned_role_rec
    QString RoleSql = "INSERT INTO tb_user_owned_role_rec VALUE(";
    RoleSql += addUser_View->userID_Edit->text()+","+roleMap.key(addUser_View->role_Box->currentText())+")";

    //执行sql语句
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(UserSql);
    bool ok2 = query.exec(RoleSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }
    QMessageBox::information(this,"提示","用户新增成功!!");
    //生成日志
    QString LogDec = "新增用户:" + addUser_View->userName_Edit->text();
    pLog->InsertUserLogDb(pUser->UserID,4,1,1,LogDec);
    addUser_View->close();
    usertableModel->submitAll();
}
