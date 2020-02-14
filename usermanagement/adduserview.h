#ifndef ADDUSERVIEW_H
#define ADDUSERVIEW_H

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

class AddUserView : public QDialog
{
    Q_OBJECT
public:
    AddUserView(QWidget *parent = nullptr);
    ~AddUserView();

    QPushButton *addUser_PB;
    QLineEdit *userID_Edit; //id
    QLineEdit *userName_Edit; //name
    QLineEdit *passWorld_Edit; //密码
    QLineEdit *realName_Edit; //real name
    QLineEdit *userTel_Edit; //tel
    QLineEdit *userEmail_Edit; //email
    QTextEdit *userDec_Edit; //email

signals:

public slots:
};

#endif // ADDUSERVIEW_H
