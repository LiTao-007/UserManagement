#include "rolepermissionsview.h"

RolePermissionsView::RolePermissionsView(QWidget *parent) : QWidget(parent)
{
    Creat_RolePermissionsView();
    MysqlConnect();
    Creat_TabViewMenu();
    GetPermissionsMap();

    pUser = UserInfo::GetInstance();
    AddPermissions_View = new AddPermissionsDialog(this);
    AddRole_View = new AddRoleDialog(this);
    AlterRoleInfo_View = new AlterRoleInfoDialog(this);
    AlterRolePMS_View = new AlterRolePMSDialog(this);

    connect(AddRole_pB,SIGNAL(clicked(bool)),this,SLOT(on_RoleAddView()));
    connect(AddPermissions_pB,SIGNAL(clicked(bool)),this,SLOT(on_PermissionsAddView()));

    connect(roleTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_TabViewMenu(QPoint)));

}

RolePermissionsView::~RolePermissionsView(){

}

void RolePermissionsView::Creat_TabViewMenu(){

    popMenu = new QMenu(roleTableView);
    QAction *deleteRole = new QAction("删除");
    QAction *alterRole = new QAction("修改角色");
    QAction *alterPermissions= new QAction("权限修改");
    popMenu->addAction(alterRole);
    popMenu->addAction(alterPermissions);
    popMenu->addAction(deleteRole);

    connect(alterRole,SIGNAL(triggered()),this,SLOT(on_AlterRoleInfo()));
    connect(alterPermissions,SIGNAL(triggered()),this,SLOT(on_alterPermissions()));
    connect(deleteRole,SIGNAL(triggered()),this,SLOT(on_deleteRole()));

}

//角色权限管理界面
void RolePermissionsView::Creat_RolePermissionsView(){
    QLabel *titleLabel = new QLabel("角色权限管理");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    AddRole_pB = new QPushButton("新增角色");
    AddPermissions_pB = new QPushButton("新增权限");

    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(AddRole_pB);
    layout1->addWidget(AddPermissions_pB);

    //查询
    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel * role_Name = new QLabel("角色名称");
    roleName_Edit = new QLineEdit();
    QLabel * role_Dec = new QLabel("角色描述");
    roleDEC_Edit = new QLineEdit();
    layout2->addWidget(role_Name);
    layout2->addWidget(roleName_Edit);
    layout2->addStretch();
    layout2->addWidget(role_Dec);
    layout2->addWidget(roleDEC_Edit);
    layout2->addStretch();

    QPushButton *roleSearch_pB = new QPushButton("查询");
    connect(roleSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_RoleSearch()));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(roleSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    //表格显示
    roletableModel = new QSqlTableModel(this,this->mydb);//绑定数据库
    roletableModel->setTable("tb_user_role_def");
    roletableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    roletableModel->insertColumn(2);
    roletableModel->setHeaderData(0,Qt::Horizontal,"角色编号");
    roletableModel->setHeaderData(1,Qt::Horizontal,"角色名称");
    roletableModel->setHeaderData(2,Qt::Horizontal,"角色描述");
    roletableModel->select(); //选取整个表的所有行

    roleTableView = new QTableView(this);
    roleTableView->setModel(roletableModel);
    //roleTableView->setColumnHidden(2,true); //隐藏列
    //userTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动适应窗口大小
    roleTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    //userTableView->verticalHeader()->setVisible(false);//隐藏列表头
    roleTableView->horizontalHeader()->setHighlightSections(false); //取消表头的在选中单元格时的高亮状态
    roleTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑
    roleTableView->setSelectionMode(QAbstractItemView::SingleSelection); //只选择一行
    roleTableView->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单

    QVBoxLayout *layoutv= new QVBoxLayout; //垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(roleTableView);

    this->setLayout(layoutv);

}

/**************槽函数*****************/
 //新增角色
void RolePermissionsView::on_RoleAddView(){
    /*
    QStandardItem* item2 = new QStandardItem(QStringLiteral("超级管理员"));
    item2->setCheckable(true);
    QStandardItem* item3 = new QStandardItem(QStringLiteral("领导"));
    item3->setCheckable(true);
    item3->setCheckState(Qt::Checked);
    item1->appendRow(item2);
    item1->appendRow(item3);
    */
    int num = AddRole_View->item1->rowCount();
    AddRole_View->item1->removeRows(0,num);
    QMap<QString, QString>::const_iterator i;
    for( i=PermissionsMap.constBegin(); i!=PermissionsMap.constEnd(); ++i)
    {
        //addUser_View->role_Box->addItem(i.value());
        QStandardItem* itemchannel = new QStandardItem(QStringLiteral("%1").arg(i.key()));
        itemchannel->setCheckable(true);
        AddRole_View->item1->appendRow(itemchannel);
        AddRole_View->item1->setChild(itemchannel->index().row(),1,new QStandardItem(QStringLiteral("%1").arg(i.value())));
    }
    AddRole_View->show();
}
//新增权限
void RolePermissionsView::on_PermissionsAddView(){
    if(!pUser->PermissionIDList.contains("9")){
        QMessageBox::warning(this,"warning","该用户无该权限!!");
        return;
    }
    AddPermissions_View->show();
    connect(AddPermissions_View->addPermissions_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertPermissionsDb()));
}

void RolePermissionsView::on_InsertPermissionsDb(){
    if(AddPermissions_View->permissionsID_Edit->text().isEmpty()
            ||AddPermissions_View->permissionsName_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","用户编号、名称和密码不能为空!");
        return;
    }
    //相关数据插入对应数据表中
    QSqlQuery query(this->mydb);
    //权限表 tb_user_permission_def
    QString PermissionsSql = "INSERT INTO tb_user_permission_def VALUE( ";
    PermissionsSql += AddPermissions_View->permissionsID_Edit->text() +",'";
    PermissionsSql += AddPermissions_View->permissionsName_Edit->text() +"','";
    PermissionsSql += AddPermissions_View->permissionsDec_Edit->toPlainText()+"')";
    if(query.exec(PermissionsSql)){
        QMessageBox::information(this,"提示","权限新增成功!!");
        AddPermissions_View->close();
        GetPermissionsMap();
        //刷新权限的TreeView
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
    }

}
//右键菜单响应函数
void RolePermissionsView::on_TabViewMenu(QPoint pos){
     QModelIndex index = roleTableView->indexAt(pos);
#if 1
     if (index.isValid())
     {
         popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
     }
#endif
}

//修改角色信息
void RolePermissionsView::on_AlterRoleInfo(){
    AlterRoleInfo_View->show();
}
//修改角色权限
void RolePermissionsView::on_alterPermissions(){
    AlterRolePMS_View->show();
}
//删除角色
void RolePermissionsView::on_deleteRole(){

}

//查询
void RolePermissionsView::on_RoleSearch(){
    QString roleName =  QString("ROLE_NAME like '%%1%'").arg(roleName_Edit->text());
    QString roleDEC =  QString("DESCR like '%%1%'").arg(roleDEC_Edit->text());
    QString filterStr = "";

    if(!roleName_Edit->text().isEmpty())
        filterStr.append(roleName);
    if(!roleDEC_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(roleDEC);
    }
    roletableModel->setFilter(filterStr); //数据库模型查询 过滤器
    roletableModel->select();
}
void RolePermissionsView::GetPermissionsMap(){
    PermissionsMap.clear();
    QSqlQuery query(this->mydb);
    QString PermissionsSql = "SELECT PERMISSION_ID,PERMISSION_CONTENT,DESCR FROM tb_user_permission_def";
    query.exec(PermissionsSql);
    while (query.next()) {
        PermissionsMap.insert(query.value(0).toString(),query.value(2).toString());
    }
}
/*数据库连接*/
void RolePermissionsView::MysqlConnect(){
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
