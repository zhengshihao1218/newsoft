#ifndef LOGINFAILDIALOG_H
#define LOGINFAILDIALOG_H

#include <QDialog>

namespace Ui {
class LoginFailDialog;
}

class LoginFailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginFailDialog(QWidget *parent = nullptr);
    ~LoginFailDialog();

private:
    Ui::LoginFailDialog *ui;
};

#endif // LOGINFAILDIALOG_H
