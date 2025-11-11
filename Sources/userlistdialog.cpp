#include "userlistdialog.h"
#include "ui_userlistdialog.h"

UserListDialog::UserListDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserListDialog)
{
    ui->setupUi(this);
}

UserListDialog::~UserListDialog()
{
    delete ui;
}
