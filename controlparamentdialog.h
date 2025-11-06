#ifndef CONTROLPARAMENTDIALOG_H
#define CONTROLPARAMENTDIALOG_H

#include <QDialog>

namespace Ui {
class ControlParamentDialog;
}

class ControlParamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlParamentDialog(QWidget *parent = nullptr);
    ~ControlParamentDialog();

private:
    Ui::ControlParamentDialog *ui;
};

#endif // CONTROLPARAMENTDIALOG_H
