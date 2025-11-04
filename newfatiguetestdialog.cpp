#include "newfatiguetestdialog.h"
#include "ui_newfatiguetestdialog.h"

NewFatigueTestDialog::NewFatigueTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewFatigueTestDialog)
{
    ui->setupUi(this);
}

NewFatigueTestDialog::~NewFatigueTestDialog()
{
    delete ui;
}
