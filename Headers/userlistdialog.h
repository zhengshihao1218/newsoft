#ifndef USERLISTDIALOG_H
#define USERLISTDIALOG_H

#include <QDialog>

namespace Ui {
class UserListDialog;
}

class UserListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserListDialog(QWidget *parent = nullptr);
    ~UserListDialog();

private:
    Ui::UserListDialog *ui;
};

#endif // USERLISTDIALOG_H
