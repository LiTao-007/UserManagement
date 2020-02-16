#ifndef ALTERUSERINFODIALOG_H
#define ALTERUSERINFODIALOG_H

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
#include <QComboBox>

class AlterUserInfoDialog : public QDialog
{
    Q_OBJECT
public:
    AlterUserInfoDialog(QWidget *parent = nullptr);
    ~AlterUserInfoDialog();

    QPushButton *alterUser_PB;
    QLineEdit *userID_Edit; //id
    QLineEdit *userName_Edit; //name
    QLineEdit *passWorld_Edit; //密码
    QLineEdit *realName_Edit; //real name
    QLineEdit *userTel_Edit; //tel
    QLineEdit *userEmail_Edit; //email
    QComboBox *role_Box; //角色选择
    QTextEdit *userDec_Edit; //email
};

#endif // ALTERUSERINFODIALOG_H
