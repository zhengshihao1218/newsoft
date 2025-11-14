#ifndef CHANGE_PASWORD_DIALOG_H
#define CHANGE_PASWORD_DIALOG_H

#include <QDialog>
#include "usermanager.h"
#include "faileddialog.h"

namespace Ui {
class Change_Pasword_Dialog;
}

class Change_Pasword_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Pasword_Dialog(QWidget *parent = nullptr);
    ~Change_Pasword_Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Change_Pasword_Dialog *ui;
};

#endif // CHANGE_PASWORD_DIALOG_H
