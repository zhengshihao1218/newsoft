#ifndef USERLISTDIALOG_H
#define USERLISTDIALOG_H

#include <QDialog>
#include <Headers/adduserdialog.h>
#include "usermanager.h"
#include "adduserdialog.h"

namespace Ui {
class UserListDialog;
}

class UserListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserListDialog(QWidget *parent = nullptr);
    ~UserListDialog();

private slots:
    void on_pushButton_addUser_clicked();
    void refreshUserList();

private:
    Ui::UserListDialog *ui;
    void populateTable();
};

#endif // USERLISTDIALOG_H
