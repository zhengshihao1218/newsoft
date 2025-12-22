#ifndef NEWINDICATTESTDIALOG_H
#define NEWINDICATTESTDIALOG_H

#include <QDialog>
#include "HMIKernel/include/global.h"

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

private:
    Ui::NewIndicatTestDialog *ui;
    int current_speed_count;
};

#endif // NEWINDICATTESTDIALOG_H
