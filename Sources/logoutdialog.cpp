#include "Headers/logoutdialog.h"
#include "ui_logoutdialog.h"

LogoutDialog::LogoutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogoutDialog)
{
    ui->setupUi(this);
}

LogoutDialog::~LogoutDialog()
{
    delete ui;
}

void LogoutDialog::on_buttonBox_accepted()
{
    emit logout();
}

