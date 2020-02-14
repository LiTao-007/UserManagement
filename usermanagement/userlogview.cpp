#include "userlogview.h"

UserLogView::UserLogView(QWidget *parent) : QWidget(parent)
{
    Creat_UserLogView();
}

UserLogView::~UserLogView(){

}

//用户日志界面
void UserLogView::Creat_UserLogView(){
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
    logLevel_Edit->addItem("所有");
    logLevel_Edit->addItem("1");
    logLevel_Edit->addItem("2");
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
    connect(logSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserLogSearch()));

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
    logtableModel = new QSqlTableModel(this,this->mydb);//绑定数据库
    logtableModel->setTable("v_log_operator");
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

    this->setLayout(layoutv);
}


void UserLogView::on_UserLogSearch(){

    QString logUSERNAME    =  QString("USER_NAME like '%%1%'").arg(logUserName_Edit->text());
    QString logPermissionDec=  QString("PERMISSION_DESCR like '%%1%'").arg(logPermissionDef_Edit->text());
    QString log_Level =  QString("LOG_LEVEL = %1").arg(logLevel_Edit->currentText());

    QString logStartDate = QString("UNIX_TIMESTAMP(`LOG_TIME`) > %1").arg(logStartDate_Edit->dateTime().toTime_t());
    QString logEndDate = QString("UNIX_TIMESTAMP(`LOG_TIME`) < %1").arg((logEndDate_Edit->dateTime().toTime_t()+86399));
    QString filterStr = "";

    if(!logUserName_Edit->text().isEmpty())
        filterStr.append(logUSERNAME);
    if(!logPermissionDef_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(logPermissionDec);
    }

    if(QString::compare(logLevel_Edit->currentText(),"所有")!=0)
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(log_Level);
    }

    if(!logStartDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(logStartDate);
    }
    if(!logEndDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(logEndDate);
    }
    qDebug()<<filterStr;
    logtableModel->setFilter(filterStr);
    logtableModel->select();

}

/*数据库连接*/
void UserLogView::MysqlConnect(){
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


