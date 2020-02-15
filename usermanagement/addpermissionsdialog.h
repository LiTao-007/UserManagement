#ifndef ADDPERMISSIONSDIALOG_H
#define ADDPERMISSIONSDIALOG_H

#include <QWidget>
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

class AddPermissionsDialog : public QDialog
{
    Q_OBJECT
public:
    AddPermissionsDialog(QWidget *parent = nullptr);
    ~AddPermissionsDialog();

    QPushButton *addPermissions_PB;
    QLineEdit *permissionsID_Edit;      //roleid
    QLineEdit *permissionsName_Edit;    //name
    QTextEdit *permissionsDec_Edit;     //dec

signals:

public slots:

};

#endif // ADDPERMISSIONSDIALOG_H
