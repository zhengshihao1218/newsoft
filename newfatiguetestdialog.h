#ifndef NEWFATIGUETESTDIALOG_H
#define NEWFATIGUETESTDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class NewFatigueTestDialog;
}

class NewFatigueTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFatigueTestDialog(QWidget *parent = nullptr);
    ~NewFatigueTestDialog();


private slots:
    void on_A1_valueChanged(double arg1);

    void on_B1_valueChanged(double arg1);

    void on_a1_valueChanged(double arg1);

    void on_b1_valueChanged(double arg1);

    void initQCustomPlot();

    void onPlotValueChange();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewFatigueTestDialog *ui;
};

#endif // NEWFATIGUETESTDIALOG_H
