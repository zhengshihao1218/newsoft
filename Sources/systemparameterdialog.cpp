#include "Headers/systemparameterdialog.h"
#include "ui_systemparameterdialog.h"

SystemParameterDialog::SystemParameterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SystemParameterDialog)
{
    ui->setupUi(this);
}

SystemParameterDialog::~SystemParameterDialog()
{
    delete ui;
}
