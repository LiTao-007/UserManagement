#include "addpermissionsdialog.h"

AddPermissionsDialog::AddPermissionsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("新增用户"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(240,340);

    addPermissions_PB = new QPushButton("确认");
    QLabel *permissionsID = new QLabel("权限编号");
    permissionsID_Edit = new QLineEdit;
    QLabel *permissionsName = new QLabel("权限名称");
    permissionsName_Edit = new QLineEdit;
    QLabel *permissionsDec = new QLabel("权限描述");
    permissionsDec_Edit = new QTextEdit;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(permissionsID,0,0);
    gridLayout->addWidget(permissionsID_Edit,0,1);
    gridLayout->addWidget(permissionsName,1,0);
    gridLayout->addWidget(permissionsName_Edit,1,1);
    gridLayout->addWidget(permissionsDec,2,0);
    gridLayout->addWidget(permissionsDec_Edit,2,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addWidget(addPermissions_PB);
    this->setLayout(vLayout);
}

AddPermissionsDialog::~AddPermissionsDialog(){

}
