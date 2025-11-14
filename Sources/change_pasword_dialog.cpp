#include "Headers/change_pasword_dialog.h"
#include "ui_change_pasword_dialog.h"

Change_Pasword_Dialog::Change_Pasword_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Change_Pasword_Dialog)
{
    ui->setupUi(this);
    ui->error_info->setStyleSheet("color: red;");
}

Change_Pasword_Dialog::~Change_Pasword_Dialog()
{
    delete ui;
}

void Change_Pasword_Dialog::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text() == "" ||  ui->lineEdit->text() == ""){
        ui->error_info->setText("不能是空");
    }
    if(ui->lineEdit_2->text() == ui->lineEdit->text()) {
        qDebug() << "Change_Pasword_Dialog updateUserPassword begin";
        int changePassword_callback = UserManager::getInstance().updateUserPassword(
            UserManager::getInstance().login_User_ID,
            ui->lineEdit->text()
            );
        qDebug() << "Change_Pasword_Dialog updateUserPassword faish";
        switch (changePassword_callback) {
        case 1:
            this->close();
            break;
        case 0:
        case -1:
        default:
            FailedDialog *dialog = new FailedDialog("修改密码失败");
            dialog->setWindowFlag(Qt::WindowCloseButtonHint);
            dialog->exec();
            delete dialog;
            dialog = nullptr;
            break;
        }
    }else {
        ui->error_info->setText("确认密码和新密码不同");
    }
}


void Change_Pasword_Dialog::on_pushButton_2_clicked()
{
    this->close();
}


void Change_Pasword_Dialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->error_info->setText("");
}


void Change_Pasword_Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->error_info->setText("");
}

