#include "Headers/newindicattestdialog.h"
#include "ui_newindicattestdialog.h"

NewIndicatTestDialog::NewIndicatTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewIndicatTestDialog)
{
    ui->setupUi(this);
}

NewIndicatTestDialog::~NewIndicatTestDialog()
{
    delete ui;
}

void NewIndicatTestDialog::on_buttonBox_accepted()
{
    this->close();
}


void NewIndicatTestDialog::on_buttonBox_rejected()
{
    this->close();
}

