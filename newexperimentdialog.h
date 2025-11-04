#ifndef NEWEXPERIMENTDIALOG_H
#define NEWEXPERIMENTDIALOG_H

#include <QDialog>
#include "newfatiguetestdialog.h"

namespace Ui {
class NewExperimentDialog;
}

class NewExperimentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewExperimentDialog(QWidget *parent = nullptr);
    ~NewExperimentDialog();

private slots:

    void on_newFatigueTestButton_clicked();

    void on_newLuboTestButton_clicked();

    void on_newIndicatButton_clicked();

    void on_newSlowFrictionButton_clicked();

    void on_newRigidityTestButton_clicked();

private:
    Ui::NewExperimentDialog *ui;
};

#endif // NEWEXPERIMENTDIALOG_H
