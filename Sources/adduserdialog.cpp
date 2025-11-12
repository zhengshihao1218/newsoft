#include "Headers/adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->error_info->setText("");
    ui->error_info->setStyleSheet("color: red;");
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}


void AddUserDialog::on_pushButton_clicked()
{
    int privilege = -1;
    if(ui->comboBox->currentText() == "操作员")
    {
        privilege = 1;
    } else if(ui->comboBox->currentText() == "管理员")
    {
        privilege = 0;
    }
    int addUser_callback = UserManager::getInstance().addUser(
        ui->lineEdit_id->text(),
        ui->lineEdit_password->text(),
        ui->lineEdit_name->text(),
        privilege
        );
    if (addUser_callback == 1){
        emit addUserSuccess();
        this->close();
    } else if(addUser_callback == -1){
        qDebug() << "添加用户失败";
        ui->error_info->setText("账号已存在");
    } else if(addUser_callback == 0) {
        qDebug() << "添加用户失败";
        ui->error_info->setText("添加用户失败");
    }
}


void AddUserDialog::on_lineEdit_password_editingFinished()
{
    checkEmpty();
}


void AddUserDialog::on_lineEdit_name_editingFinished()
{
    checkEmpty();
}


void AddUserDialog::on_lineEdit_id_editingFinished()
{
    checkEmpty();
}


void AddUserDialog::checkEmpty()
{
    if(ui->lineEdit_id->text()!="" && ui->lineEdit_name->text()!="" && ui->lineEdit_password->text()!=""){
        ui->pushButton->setEnabled(true);
    } else{
        ui->pushButton->setEnabled(false);
    }
}

