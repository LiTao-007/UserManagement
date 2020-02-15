#ifndef ALTERUSERROLEDIALOG_H
#define ALTERUSERROLEDIALOG_H

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

class AlterUserRoleDialog : public QDialog
{
    Q_OBJECT
public:
    AlterUserRoleDialog(QWidget *parent = nullptr);
    ~AlterUserRoleDialog();

    QPushButton *alterRole_PB;
    QLineEdit *userName_Edit; //name
    QStandardItemModel* roleModel;
    QTreeView* roleTreeView;


};

#endif // ALTERUSERROLEDIALOG_H
