#include "Headers/browseexperimentdialog.h"
#include "ui_browseexperimentdialog.h"

BrowseExperimentDialog::BrowseExperimentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BrowseExperimentDialog)
{
    ui->setupUi(this);
}

BrowseExperimentDialog::~BrowseExperimentDialog()
{
    delete ui;
}
