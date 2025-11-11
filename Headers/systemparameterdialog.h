#ifndef SYSTEMPARAMETERDIALOG_H
#define SYSTEMPARAMETERDIALOG_H

#include <QDialog>

namespace Ui {
class SystemParameterDialog;
}

class SystemParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemParameterDialog(QWidget *parent = nullptr);
    ~SystemParameterDialog();

private:
    Ui::SystemParameterDialog *ui;
};

#endif // SYSTEMPARAMETERDIALOG_H
