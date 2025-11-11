#ifndef LOGOUTDIALOG_H
#define LOGOUTDIALOG_H

#include <QDialog>

namespace Ui {
class LogoutDialog;
}

class LogoutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogoutDialog(QWidget *parent = nullptr);
    ~LogoutDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LogoutDialog *ui;

signals:
    void logout();
};

#endif // LOGOUTDIALOG_H
