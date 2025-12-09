#ifndef NEWFATIGUETESTDIALOG_H
#define NEWFATIGUETESTDIALOG_H

#include <QDialog>
#include "qcustomplot.h"
#include "HMIKernel/include/global.h"
#include <QDateTime>

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

    void initQCustomPlot();

    void onPlotValueChange();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_COMP_AXIS1_TEST_FORMULA_A_valueChanged(double arg1);

    void on_COMP_AXIS1_TEST_FORMULA_B_valueChanged(double arg1);

    void on_COMP_AXIS1_TEST_FORMULA_ALPHA_valueChanged(double arg1);

    void on_COMP_AXIS1_TEST_FORMULA_BETA_valueChanged(double arg1);

private:
    Ui::NewFatigueTestDialog *ui;
    QString incrementStringSuffix(const QString& input);

signals:
    void newTestComp();
};

#endif // NEWFATIGUETESTDIALOG_H
