#ifndef NEWINDICATTESTDIALOG_H
#define NEWINDICATTESTDIALOG_H

#include <QDialog>
#include "HMIKernel/include/global.h"
#include "Headers/mainwindow.h"

namespace Ui {
class NewIndicatTestDialog;
}

class NewIndicatTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewIndicatTestDialog(QWidget *parent = nullptr);
    ~NewIndicatTestDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

    void on_COMP_AXIS1_TEST_TABLE_WT1_VEL_valueChanged(double arg1);

    void on_doubleSpinBox_34_valueChanged(double arg1);

    void on_COMP_AXIS1_TEST_TABLE_WT2_VEL_valueChanged(double arg1);

    void on_doubleSpinBox_41_valueChanged(double arg1);

    void on_COMP_AXIS1_TEST_TABLE_WT3_VEL_valueChanged(double arg1);

    void on_doubleSpinBox_48_valueChanged(double arg1);

private:
    Ui::NewIndicatTestDialog *ui;
    int current_speed_count;
    QString incrementStringSuffix(const QString& input);
    double calculate_frequency_from_velocity_amplitude(double velocity_mps, double amplitude_mm);

signals:
    void newTestComp();
};


#endif // NEWINDICATTESTDIALOG_H
