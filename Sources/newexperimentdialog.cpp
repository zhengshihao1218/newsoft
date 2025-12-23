#include "Headers/newexperimentdialog.h"
#include "ui_newexperimentdialog.h"

NewExperimentDialog::NewExperimentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewExperimentDialog)
{
    ui->setupUi(this);
}

NewExperimentDialog::~NewExperimentDialog()
{
    delete ui;
}

void NewExperimentDialog::on_newFatigueTestButton_clicked()
{
    NewFatigueTestDialog *dialog = new NewFatigueTestDialog();
    connect(dialog, &NewFatigueTestDialog::newTestComp, this, &NewExperimentDialog::newFatigueTest);
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    this->hide();
    dialog->exec();
    delete dialog;
    dialog = nullptr;
    this->close();
}


void NewExperimentDialog::on_newLuboTestButton_clicked()
{

}


void NewExperimentDialog::on_newIndicatButton_clicked()
{
    NewIndicatTestDialog *dialog = new NewIndicatTestDialog();
    connect(dialog, &NewIndicatTestDialog::newTestComp, this, &NewExperimentDialog::newIndicatTest);
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    this->hide();
    dialog->exec();
    delete dialog;
    dialog = nullptr;
    this->close();
}


void NewExperimentDialog::on_newSlowFrictionButton_clicked()
{

}


void NewExperimentDialog::on_newRigidityTestButton_clicked()
{

}

