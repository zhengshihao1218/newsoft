#ifndef CONTROLPARAMENTDIALOG_H
#define CONTROLPARAMENTDIALOG_H

#include <QDialog>
#include <QTimer>
#include "HMIKernel/include/global.h"

namespace Ui {
class ControlParamentDialog;
}

class ControlParamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlParamentDialog(QWidget *parent = nullptr);
    ~ControlParamentDialog();

private slots:
    void on_tabWidget_2_currentChanged(int index);

private:
    Ui::ControlParamentDialog *ui;
    QTimer* tmUpdate;
    void updateDBValue();
};

#endif // CONTROLPARAMENTDIALOG_H
