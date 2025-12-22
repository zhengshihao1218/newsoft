#include "Headers/newindicattestdialog.h"
#include "ui_newindicattestdialog.h"

NewIndicatTestDialog::NewIndicatTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewIndicatTestDialog)
{
    ui->setupUi(this);
    ui->widget_4->setVisible(false);
    ui->widget_5->setVisible(false);
    ui->widget_6->setVisible(false);
    ui->widget_7->setVisible(false);
    ui->widget_8->setVisible(false);
    current_speed_count = 3;
}

NewIndicatTestDialog::~NewIndicatTestDialog()
{
    delete ui;
}

void NewIndicatTestDialog::on_buttonBox_accepted()
{
    SetDBValue("COMP_AXIS1_TEST_SUBMOTIONTYPE",2);
    this->close();
}


void NewIndicatTestDialog::on_buttonBox_rejected()
{
    this->close();
}


void NewIndicatTestDialog::on_pushButton_clicked()
{
    if(current_speed_count < 8){ //最大速度数量
        current_speed_count ++;
        switch (current_speed_count) {
        case 4:
            ui->widget_4->setVisible(true);
            break;
        case 5:
            ui->widget_5->setVisible(true);
            break;
        case 6:
            ui->widget_6->setVisible(true);
            break;
        case 7:
            ui->widget_7->setVisible(true);
            break;
        case 8:
            ui->widget_8->setVisible(true);
            break;
        default:
            break;
        }
    }
}

