#include "alterrolepmsdialog.h"

AlterRolePMSDialog::AlterRolePMSDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("角色权限修改"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(230,350);
    alterPermissions_PB = new QPushButton("修改确认");
    QLabel *roleID = new QLabel("角色编号");
    roleID_Edit = new QLineEdit;
    QLabel *roleName = new QLabel("角色名称");
    roleName_Edit = new QLineEdit;
    QLabel *userDec = new QLabel("角色描述");
    //roleDec_Edit = new QTextEdit;
    roleDec_Edit = new QLineEdit;
	
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(roleID,0,0);
    gridLayout->addWidget(roleID_Edit,0,1);
    gridLayout->addWidget(roleName,1,0);
    gridLayout->addWidget(roleName_Edit,1,1);
    gridLayout->addWidget(userDec,2,0);
    gridLayout->addWidget(roleDec_Edit,2,1);

    permissionsTreeView = new QTreeView(this);
    permissionsModel = new QStandardItemModel(permissionsTreeView);
    permissionsModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("角色权限选择")<<QStringLiteral(" "));     //设置列头
    item1 = new QStandardItem(QStringLiteral("权限编号"));
    permissionsModel->appendRow(item1);
    permissionsModel->setItem(permissionsModel->indexFromItem(item1).row(),1,new QStandardItem(QStringLiteral("权限内容")));
 /*
    QStandardItem* item2 = new QStandardItem(QStringLiteral("超级管理员"));
    item2->setCheckable(true);
    QStandardItem* item3 = new QStandardItem(QStringLiteral("领导"));
    item3->setCheckable(true);
    item3->setCheckState(Qt::Checked);
    item1->appendRow(item2);
    item1->appendRow(item3);
*/
    permissionsTreeView->setModel(permissionsModel);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);

    vLayout->addWidget(permissionsTreeView);
    vLayout->addWidget(alterPermissions_PB);
    setLayout(vLayout);
}

AlterRolePMSDialog::~AlterRolePMSDialog(){

}
