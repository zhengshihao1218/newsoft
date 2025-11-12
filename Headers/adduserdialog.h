#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

private slots:

    void on_pushButton_clicked();

    void on_lineEdit_password_editingFinished();

    void on_lineEdit_name_editingFinished();

    void on_lineEdit_id_editingFinished();

private:
    Ui::AddUserDialog *ui;
    void checkEmpty();
signals:
    void addUserSuccess();
};

#endif // ADDUSERDIALOG_H
