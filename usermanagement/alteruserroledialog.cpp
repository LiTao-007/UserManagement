#include "alteruserroledialog.h"

AlterUserRoleDialog::AlterUserRoleDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("用户角色 修改"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(230,350);
    alterRole_PB = new QPushButton("修改确认");
    QLabel *userName = new QLabel("用户名称");
    userName_Edit = new QLineEdit;

    roleTreeView = new QTreeView(this);
    roleModel = new QStandardItemModel(roleTreeView);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(userName,0,0);
    gridLayout->addWidget(userName_Edit,0,1);
    roleModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("系统角色"));     //设置列头
    QStandardItem* item1 = new QStandardItem(QStringLiteral("用户选择角色"));
    roleModel->appendRow(item1);
    QStandardItem* item2 = new QStandardItem(QStringLiteral("超级管理员"));
    item2->setCheckable(true);
    QStandardItem* item3 = new QStandardItem(QStringLiteral("领导"));
    item3->setCheckable(true);
    item3->setCheckState(Qt::Checked);
    item1->appendRow(item2);
    item1->appendRow(item3);

    roleTreeView->setModel(roleModel);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);

    vLayout->addWidget(roleTreeView);
    vLayout->addWidget(alterRole_PB);
    setLayout(vLayout);
}

AlterUserRoleDialog::~AlterUserRoleDialog(){

}
