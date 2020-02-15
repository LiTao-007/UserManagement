#include "alterroleinfodialog.h"

AlterRoleInfoDialog::AlterRoleInfoDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("角色信息修改"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(230,300);

	alterRole_PB = new QPushButton("确认");
    QLabel *roleID = new QLabel("角色编号");
    roleID_Edit = new QLineEdit;
    QLabel *roleName = new QLabel("角色名称");
    roleName_Edit = new QLineEdit;
    QLabel *userDec = new QLabel("角色描述");
    roleDec_Edit = new QTextEdit;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(roleID,0,0);
    gridLayout->addWidget(roleID_Edit,0,1);
    gridLayout->addWidget(roleName,1,0);
    gridLayout->addWidget(roleName_Edit,1,1);
    gridLayout->addWidget(userDec,2,0);
    gridLayout->addWidget(roleDec_Edit,2,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(alterRole_PB);
    setLayout(vLayout);
}

AlterRoleInfoDialog::~AlterRoleInfoDialog(){

}
