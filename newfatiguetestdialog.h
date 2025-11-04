#ifndef NEWFATIGUETESTDIALOG_H
#define NEWFATIGUETESTDIALOG_H

#include <QDialog>

namespace Ui {
class NewFatigueTestDialog;
}

class NewFatigueTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFatigueTestDialog(QWidget *parent = nullptr);
    ~NewFatigueTestDialog();

private:
    Ui::NewFatigueTestDialog *ui;
};

#endif // NEWFATIGUETESTDIALOG_H
