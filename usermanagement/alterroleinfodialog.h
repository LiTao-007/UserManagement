#ifndef ALTERROLEINFODIALOG_H
#define ALTERROLEINFODIALOG_H

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

class AlterRoleInfoDialog : public QDialog
{
    Q_OBJECT
public:
    AlterRoleInfoDialog(QWidget *parent = nullptr);
    ~AlterRoleInfoDialog();

    QPushButton *alterRole_PB;
    QLineEdit *roleID_Edit; //roleid
    QLineEdit *roleName_Edit; //name
    QTextEdit *roleDec_Edit; //dec
};

#endif // ALTERROLEINFODIALOG_H
