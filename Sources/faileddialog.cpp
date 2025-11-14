#include "Headers/faileddialog.h"
#include "ui_faileddialog.h"

FailedDialog::FailedDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FailedDialog)
{
    ui->setupUi(this);
}

// 带消息参数的构造函数
FailedDialog::FailedDialog(const QString &message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailedDialog)
{
    ui->setupUi(this);
    ui->label_2->setText(message);
}


FailedDialog::~FailedDialog()
{
    delete ui;
}
