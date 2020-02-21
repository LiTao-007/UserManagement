#include "rolepermissionsview.h"

RolePermissionsView::RolePermissionsView(QWidget *parent) : QWidget(parent)
{
    Creat_RolePermissionsView();
    Creat_TabViewMenu();
    GetPermissionsMap();

    pUser = UserInfo::GetInstance();
    pLog = LogModel::GetInstance();
    mydb = pLog->pDb->myDb;

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
    //QAction *alterRole = new QAction("修改角色");
    QAction *alterPermissions= new QAction("角色修改");
    //popMenu->addAction(alterRole);
    popMenu->addAction(alterPermissions);
    popMenu->addAction(deleteRole);


   // connect(alterRole,SIGNAL(triggered()),this,SLOT(on_AlterRoleInfo()));
    connect(alterPermissions,SIGNAL(triggered()),this,SLOT(on_alterRole()));
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
    //权限判断
    if(!pUser->PermissionIDList.contains("7")){
        QMessageBox::warning(this,"warning","该用户无该权限!!");
        return;
    }
    int num = AddRole_View->item1->rowCount();
    AddRole_View->item1->removeRows(0,num); //清空子节点
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
    connect(AddRole_View->addRole_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertRoleDb()));
}
void RolePermissionsView::on_InsertRoleDb(){
    QMap<QString, QString> PerIDMap;
    int PerNum=0;
    //获取勾选的权限
    if(AddRole_View->item1->hasChildren()){
        for(int i = 0;i < AddRole_View->item1->rowCount() ;i++){
            QStandardItem * childitem = AddRole_View->item1->child(i);
            //qDebug() << "childitem = " << childitem->text() <<" "<<childitem->checkState();
            if(childitem->checkState()){
                QModelIndex index = childitem->index();
                index = index.sibling(index.row(),1); //第二列内容
                QString roleDce =AddRole_View->roleTreeView->model()->itemData(index).values()[0].toString();
                //qDebug()<< roleTableView->model()->itemData(index).values()[0].toString();
                PerIDMap.insert(childitem->data(0).toString(),roleDce);
                PerNum++;
            }
        }
    }
    //相关数据插入对应数据表中

    //角色表 tb_user_role_def
    QString RoleSql = "INSERT INTO tb_user_role_def VALUE( ";
    RoleSql += AddRole_View->roleID_Edit->text()+",'";
    RoleSql += AddRole_View->roleName_Edit->text()+"','";
    RoleSql += AddRole_View->roleDec_Edit->text() + "')";

    //角色权限表 tb_user_role_permissions_def
    QString RolePMSSql = "INSERT INTO tb_user_role_permissions_def VALUE(";
    QMap<QString, QString>::const_iterator itr;
    for(itr = PerIDMap.constBegin();itr != PerIDMap.constEnd();++itr){
        RolePMSSql.append(AddRole_View->roleID_Edit->text());
        RolePMSSql.append(",");
        RolePMSSql.append(itr.key());
        RolePMSSql.append(",'");
        RolePMSSql.append(itr.value());
        PerNum--;
        if(PerNum > 0){
            RolePMSSql.append("'),(");
        }else {
            RolePMSSql.append("')");
            break;
        }
    }
#if 1
    //执行sql语句
    QSqlQuery query(this->mydb);
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(RoleSql);
    bool ok2 = query.exec(RolePMSSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }
    QMessageBox::information(this,"提示","角色新增成功!!");
#endif
    //生成日志
    QString LogDec = "新增角色:" + AddRole_View->roleName_Edit->text();
    pLog->InsertUserLogDb(pUser->UserID,4,7,1,LogDec);
    AddRole_View->close();
    roletableModel->submitAll();
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
    if(!query.exec(PermissionsSql)){
        QMessageBox::warning(this,"warning",query.lastError().text());
    }
    QMessageBox::information(this,"提示","权限新增成功!!");
    //生成日志
    QString LogDec = "新增权限:" + AddPermissions_View->permissionsName_Edit->text();
    pLog->InsertUserLogDb(pUser->UserID,4,9,1,LogDec);

    AddPermissions_View->close();
    GetPermissionsMap();

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

//修改角色信息 ------和权限修改合并
void RolePermissionsView::on_AlterRoleInfo(){

    //AlterRoleInfo_View->show();
}
//修改角色权限和信息
void RolePermissionsView::on_alterRole(){
    if(!pUser->PermissionIDList.contains("10")){
        QMessageBox::warning(this,"warning","该用户无新增用户权限!!");
        return;
    }
    //获取当前选择行的角色信息
    RoleInfoList.clear();
    int row = roleTableView->currentIndex().row();
    qDebug()<< row;
    int i;
    for(i = 0; i < 3; i++)
    {
        //遍历第row行的所有信息
        QModelIndex index = roletableModel->index(row,i);
        QString name = roletableModel->data(index).toString();
        RoleInfoList<<name;
    }
    AlterRolePMS_View->roleID_Edit->setText(RoleInfoList.at(0));
    AlterRolePMS_View->roleID_Edit->setReadOnly(true);
    AlterRolePMS_View->roleName_Edit->setText(RoleInfoList.at(1));
    AlterRolePMS_View->roleDec_Edit->setText(RoleInfoList.at(2));

    //获取选择角色的权限ID
    QStringList role_PermissionsList;
    QSqlQuery query(this->mydb);
    QString RolePerID = "select PERMISSION_ID from tb_user_role_permissions_def where ROLE_ID = "+RoleInfoList.at(0);
    query.exec(RolePerID);
    while (query.next()) {
        role_PermissionsList.append(query.value(0).toString());
    }
    //添加子节点
    int num = AlterRolePMS_View->item1->rowCount();
    AlterRolePMS_View->item1->removeRows(0,num); //清空子节点
    QMap<QString, QString>::const_iterator itr;
    for( itr=PermissionsMap.constBegin(); itr!=PermissionsMap.constEnd(); ++itr)
    {
        //addUser_View->role_Box->addItem(i.value());
        QStandardItem* itemchannel = new QStandardItem(QStringLiteral("%1").arg(itr.key()));
        itemchannel->setCheckable(true);
        if(role_PermissionsList.contains(itr.key())){ //角色已有权限勾上
            itemchannel->setCheckState(Qt::Checked);
        }
        AlterRolePMS_View->item1->appendRow(itemchannel);
        AlterRolePMS_View->item1->setChild(itemchannel->index().row(),1,new QStandardItem(QStringLiteral("%1").arg(itr.value())));
    }
    AlterRolePMS_View->show();
    connect(AlterRolePMS_View->alterPermissions_PB,SIGNAL(clicked(bool)),this,SLOT(on_AlterRoleDb()));
}
void RolePermissionsView::on_AlterRoleDb(){
    if(AlterRolePMS_View->roleName_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","角色名称不能为空!");
        return;
    }
    //获取Sql语句
    QMap<QString, QString> PerIDMap;
    int PerNum=0;
    //获取勾选的权限
    if(AlterRolePMS_View->item1->hasChildren()){
        for(int i = 0;i < AlterRolePMS_View->item1->rowCount() ;i++){
            QStandardItem * childitem = AlterRolePMS_View->item1->child(i);
            //qDebug() << "childitem = " << childitem->text() <<" "<<childitem->checkState();
            if(childitem->checkState()){
                QModelIndex index = childitem->index();
                index = index.sibling(index.row(),1); //第二列内容
                QString roleDce =AlterRolePMS_View->permissionsTreeView->model()->itemData(index).values()[0].toString();
                //qDebug()<< roleTableView->model()->itemData(index).values()[0].toString();
                PerIDMap.insert(childitem->data(0).toString(),roleDce);
                PerNum++;
            }
        }
    }

    //角色表 tb_user_role_def
    QString RoleSql = "INSERT INTO tb_user_role_def VALUE( ";
    RoleSql += AlterRolePMS_View->roleID_Edit->text()+",'";
    RoleSql += AlterRolePMS_View->roleName_Edit->text()+"','";
    RoleSql += AlterRolePMS_View->roleDec_Edit->text() + "')";

    //角色权限表 tb_user_role_permissions_def
    QString RolePMSSql = "INSERT INTO tb_user_role_permissions_def VALUE(";
    QMap<QString, QString>::const_iterator itr;
    for(itr = PerIDMap.constBegin();itr != PerIDMap.constEnd();++itr){
        RolePMSSql.append(AlterRolePMS_View->roleID_Edit->text());
        RolePMSSql.append(",");
        RolePMSSql.append(itr.key());
        RolePMSSql.append(",'");
        RolePMSSql.append(itr.value());
        PerNum--;
        if(PerNum > 0){
            RolePMSSql.append("'),(");
        }else {
            RolePMSSql.append("')");
            break;
        }
    }
    //删除role
    QString delRolePerSql = "DELETE FROM tb_user_owned_role_rec WHERE ROLE_ID = "+RoleInfoList.at(0);
    //删除角色权限
    QString delRoleSql = "DELETE FROM tb_user_role_def WHERE ROLE_ID = "+RoleInfoList.at(0);

    int choose;
    choose = QMessageBox::question(this, tr("修改角色"),
                                   QString(tr("确认修改该角色")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No)
     {
        return;
     }
    //执行sql语句
    QSqlQuery query(this->mydb);
    //执行sql语句
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(delRolePerSql);
    bool ok2 = query.exec(delRoleSql);
    bool ok3 = query.exec(RoleSql);
    bool ok4 = query.exec(RolePMSSql);
    if(ok1&&ok2&&ok3&&ok4)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }
    QMessageBox::information(this,"提示","角色修改成功!!");

    //生成日志
    QString LogDec = "修改角色:" + AlterRolePMS_View->roleName_Edit->text();
    pLog->InsertUserLogDb(pUser->UserID,4,10,1,LogDec);

    AlterRolePMS_View->close();
    roletableModel->submitAll();

}


//删除角色
void RolePermissionsView::on_deleteRole(){
    if(!pUser->PermissionIDList.contains("8")){
        QMessageBox::warning(this,"warning","该用户无新增用户权限!!");
        return;
    }

    //获取当前选择行的用户信息
    QStringList RoleInfoList;
    int row = roleTableView->currentIndex().row();
    qDebug()<< row;
    int i;
    for(i = 0; i < 3; i++)
    {
        //遍历第row行的所有信息
        QModelIndex index = roletableModel->index(row,i);
        QString name = roletableModel->data(index).toString();
        RoleInfoList<<name;
    }
    int choose;
    choose = QMessageBox::question(this, tr("删除角色"),
                                   QString(tr("确认删除该角色")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No)
     {
        return;
     }

    QSqlQuery query(this->mydb);
    // tb_user_owned_role_rec 删除角色用户关系
    QString delRoleUserSql = "DELETE FROM tb_user_owned_role_rec WHERE ROLE_ID = "+RoleInfoList.at(0);
    // tb_user_role_rec 删除角色
    QString delRoleSql = "DELETE FROM tb_user_role_def WHERE ROLE_ID = "+RoleInfoList.at(0);
    // tb_user_role_rec 删除角色和权限关系
    QString delRolePerSql="DELETE FROM tb_user_role_permissions_def WHERE ROLE_ID= "+RoleInfoList.at(0);

    //执行sql语句
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(delRoleUserSql);
    bool ok2 = query.exec(delRoleSql);
    bool ok3 = query.exec(delRolePerSql);
    if(ok1&&ok2&&ok3)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }

    //生成日志
    QString LogDec = "删除角色:" + RoleInfoList.at(1);
    pLog->InsertUserLogDb(pUser->UserID,4,8,1,LogDec);
    roletableModel->submitAll();
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

