#include "Headers/loginfaildialog.h"
#include "ui_loginfaildialog.h"

LoginFailDialog::LoginFailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginFailDialog)
{
    ui->setupUi(this);
}

LoginFailDialog::~LoginFailDialog()
{
    delete ui;
}
