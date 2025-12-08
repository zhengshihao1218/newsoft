#include "Headers/controlparamentdialog.h"
#include "ui_controlparamentdialog.h"

ControlParamentDialog::ControlParamentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ControlParamentDialog)
{
    ui->setupUi(this);
    tmUpdate = new QTimer(this);
    tmUpdate->start(100);
    connect(tmUpdate, &QTimer::timeout, this, &ControlParamentDialog::updateDBValue);
}

ControlParamentDialog::~ControlParamentDialog()
{
    delete ui;
}

void ControlParamentDialog::updateDBValue(){
    ui->label_act_posi->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_POSI").lValue / 1000.0, 'f', 3));
    ui->label_act_pear->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_PRES").lValue / 1000.0, 'f', 3));
    ui->label_act_velo->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_VELO").lValue / 1000.0, 'f', 3));
}

void ControlParamentDialog::on_tabWidget_2_currentChanged(int index)
{
    qDebug() << "on_tabWidget_2_currentChanged index == " << index;
    switch (index) {
    case 1:

        break;
    default:
        break;
    }

}

// void ControlParamentDialog::refresh(

