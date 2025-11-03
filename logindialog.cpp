#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() == "ceshi" && ui->lineEdit_2->text() == "111"){
        emit login();
    }
}

