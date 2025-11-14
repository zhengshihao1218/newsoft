#include "Headers/logindialog.h"
#include "ui_logindialog.h"
#include "Headers/mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked";
    QString id = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    qDebug() << "on_pushButton_clicked 2";
    bool loginSuccess = UserManager::getInstance().authenticate(id,password);
    if (UserManager::getInstance().authenticate(id,password)) {
        emit login(id);
        qDebug() << "账号密码OK";
        this->close();
    } else {
        FailedDialog *dialog = new FailedDialog("用户不存在或密码不正确");
        dialog->setWindowFlag(Qt::WindowCloseButtonHint);
        dialog->exec();
        delete dialog;
        dialog = nullptr;
    }
}

