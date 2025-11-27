#include "Headers/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QString hmi_version = GetHMIKernelVersion();
    ui->label_hmi_version->setText(hmi_version);
    ui->label_hmi_version->setStyleSheet("color: white;");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
