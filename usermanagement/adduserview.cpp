#include "adduserview.h"

AddUserView::AddUserView(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("新增用户"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(230,350);

    addUser_PB = new QPushButton("确认");
    QLabel *userID = new QLabel("用户编号");
    userID_Edit = new QLineEdit;
    QLabel *userName = new QLabel("用户名称");
    userName_Edit = new QLineEdit;
    QLabel *passWorld = new QLabel("密码");
    passWorld_Edit = new QLineEdit;
    QLabel *realName = new QLabel("真实姓名");
    realName_Edit = new QLineEdit;
    QLabel *userTel = new QLabel("手机号码");
    userTel_Edit = new QLineEdit;
    QLabel *userEmail = new QLabel("电子邮箱");
    userEmail_Edit = new QLineEdit;
    QLabel *userDec = new QLabel("用户描述");
    userDec_Edit = new QTextEdit;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(userID,0,0);
    gridLayout->addWidget(userID_Edit,0,1);

    gridLayout->addWidget(userName,1,0);
    gridLayout->addWidget(userName_Edit,1,1);

    gridLayout->addWidget(passWorld,2,0);
    gridLayout->addWidget(passWorld_Edit,2,1);

    gridLayout->addWidget(realName,3,0);
    gridLayout->addWidget(realName_Edit,3,1);

    gridLayout->addWidget(userTel,4,0);
    gridLayout->addWidget(userTel_Edit,4,1);

    gridLayout->addWidget(userEmail,5,0);
    gridLayout->addWidget(userEmail_Edit,5,1);

    gridLayout->addWidget(userDec,6,0);
    gridLayout->addWidget(userDec_Edit,6,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(addUser_PB);
    setLayout(vLayout);
}

AddUserView::~AddUserView(){

}
