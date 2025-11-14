#ifndef USERLISTDIALOG_H
#define USERLISTDIALOG_H

#include <QDialog>
#include <Headers/adduserdialog.h>
#include "usermanager.h"
#include "adduserdialog.h"
#include <QMessageBox>
#include "faileddialog.h"

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

    void on_pushButton_previous_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_deleteUser_clicked();

    void on_pushButton_clicked();

    void on_pushButton_serach_clicked();

private:
    Ui::UserListDialog *ui;
    void populateTable();
    int currentPage;
};

#endif // USERLISTDIALOG_H
