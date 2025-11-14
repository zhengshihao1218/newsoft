#ifndef FAILEDDIALOG_H
#define FAILEDDIALOG_H

#include <QDialog>

namespace Ui {
class FailedDialog;
}

class FailedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FailedDialog(QWidget *parent = nullptr);
    explicit FailedDialog(const QString &message, QWidget *parent = nullptr);
    ~FailedDialog();

private:
    Ui::FailedDialog *ui;
};

#endif // FAILEDDIALOG_H
