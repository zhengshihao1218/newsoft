#include "controlparamentdialog.h"
#include "ui_controlparamentdialog.h"

ControlParamentDialog::ControlParamentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ControlParamentDialog)
{
    ui->setupUi(this);
}

ControlParamentDialog::~ControlParamentDialog()
{
    delete ui;
}
