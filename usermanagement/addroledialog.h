#ifndef ADDROLEDIALOG_H
#define ADDROLEDIALOG_H

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
#include <QTreeWidget>

class AddRoleDialog : public QDialog
{
    Q_OBJECT
public:
    AddRoleDialog(QWidget *parent = nullptr);
    ~AddRoleDialog();

    QPushButton *addRole_PB;
    QLineEdit *roleID_Edit; //roleid
    QLineEdit *roleName_Edit; //name
    QTextEdit *roleDec_Edit; //dec

    QStandardItemModel* roleModel;
    QTreeView* roleTreeView;
    QStandardItem* item1; // 权限根节点

signals:

public slots:
};

#endif // ADDROLEDIALOG_H
