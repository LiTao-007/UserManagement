#ifndef ALTERROLEPMSDIALOG_H
#define ALTERROLEPMSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QStandardItemModel>

#include <QTreeWidget>

class AlterRolePMSDialog : public QDialog
{
    Q_OBJECT
public:
    AlterRolePMSDialog(QWidget *parent = nullptr);
    ~AlterRolePMSDialog();

    QPushButton *alterPermissions_PB;
    QLineEdit *roleID_Edit; //roleid
    QLineEdit *roleName_Edit; //name
    QLineEdit *roleDec_Edit;
    //QTextEdit *roleDec_Edit; //dec

    QStandardItemModel* permissionsModel;
    QTreeView* permissionsTreeView;

    QStandardItem* item1; // 权限根节点


};

#endif // ALTERROLEPMSDIALOG_H
