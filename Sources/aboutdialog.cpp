#include "Headers/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->label_hmi_version->setStyleSheet("color: white;");
    ui->label_plc_version->setStyleSheet("color: white;");
    ui->label_lib_version->setStyleSheet("color: white;");
    QString lib_version = GetHMIKernelVersion();
    ui->label_lib_version->setText(lib_version);
    ui->label_plc_version->setText(QString::number(GetDBValue("CTRL_PLCVERSION").lValue));
    ui->label_hmi_version->setText("0.1");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
