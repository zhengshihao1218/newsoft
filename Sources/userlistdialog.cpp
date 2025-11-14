#include "Headers/userlistdialog.h"
#include "ui_userlistdialog.h"

UserListDialog::UserListDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserListDialog)
{
    ui->setupUi(this);
    currentPage = 1;
    populateTable();
}

UserListDialog::~UserListDialog()
{
    delete ui;
}

void UserListDialog::on_pushButton_addUser_clicked()
{
    AddUserDialog *dialog = new AddUserDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    connect(dialog, &AddUserDialog::addUserSuccess, this, &UserListDialog::refreshUserList);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}

void UserListDialog::refreshUserList()
{
    populateTable();
}

void UserListDialog::populateTable()
{
    currentPage = 1;
    ui->tableWidget->setRowCount(0);
    QVector<UserInfo>infos = UserManager::getInstance().getUsersByPage(currentPage);
    ui->tableWidget->setRowCount(infos.size());
    for (int i = 0; i < infos.size(); ++i) {
        const UserInfo &user = infos[i];

        // UserID
        QTableWidgetItem *idItem = new QTableWidgetItem(user.UserID);
        ui->tableWidget->setItem(i, 0, idItem);

        // UserName
        QTableWidgetItem *nameItem = new QTableWidgetItem(user.UserName);
        ui->tableWidget->setItem(i, 1, nameItem);

        // Privilege
        QString privilegeText;
        switch (user.Privilege) {
        case 0: privilegeText = "管理员"; break;
        case 1: privilegeText = "操作员"; break;
        default: privilegeText = QString::number(user.Privilege);
        }
        QTableWidgetItem *privilegeItem = new QTableWidgetItem(privilegeText);
        privilegeItem->setData(Qt::UserRole, user.Privilege); // 保存原始权限值
        ui->tableWidget->setItem(i, 2, privilegeItem);

        // DataCreate
        QTableWidgetItem *dateItem = new QTableWidgetItem(user.DataCreate.toString("yyyy-MM-dd hh:mm:ss"));
        ui->tableWidget->setItem(i, 3, dateItem);

    }

    // 调整列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->tableWidget->resizeColumnsToContents();
    // for (int i = 0; i < tableWidget->columnCount(); ++i) {
    //     if (tableWidget->columnWidth(i) < 80) {
    //         tableWidget->setColumnWidth(i, 80);
    //     }
    ui->label_3->setText(QString("第 %1 页").arg(currentPage));
    int count = infos.size();
    ui->label_5->setText(QString("共 %1 条").arg(count));
    ui->label_4->setText(QString("共 %1 页").arg((count + 10 - 1) / 10));
    qDebug() << "加载了" << infos.size() << "个用户";
}

void UserListDialog::on_pushButton_previous_clicked()
{
    if(currentPage > 1){
        currentPage --;
        populateTable();
    }
}


void UserListDialog::on_pushButton_next_clicked()
{
    if(currentPage < (UserManager::getInstance().getUserCount()/10 + 1)){
        currentPage ++;
        populateTable();
    }
}


void UserListDialog::on_pushButton_deleteUser_clicked()
{
    if(ui->tableWidget->currentRow()>1){
        QString ID = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
        QString Name = ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
        int ret = QMessageBox::question(this, "确认删除",
                                        QString("确定要删除用户 '%1 (%2)' 吗？此操作不可恢复！")
                                            .arg(Name).arg(ID),
                                        QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes) {
            int result = UserManager::getInstance().deleteUser(ID);
            switch (result) {
            case 1:
                populateTable();
                break;
            default:
                FailedDialog *dialog = new FailedDialog("删除用户失败");
                dialog->setWindowFlag(Qt::WindowCloseButtonHint);
                dialog->exec();
                delete dialog;
                dialog = nullptr;
                break;
            }
        }
    }
}


void UserListDialog::on_pushButton_clicked()
{
    populateTable();
}


void UserListDialog::on_pushButton_serach_clicked()
{
    currentPage = 1;
    ui->tableWidget->setRowCount(0);
    QVector<UserInfo>infos = UserManager::getInstance().searchUsersByPage(ui->lineEdit->text(),currentPage);
    ui->tableWidget->setRowCount(infos.size());
    for (int i = 0; i < infos.size(); ++i) {
        const UserInfo &user = infos[i];

        // UserID
        QTableWidgetItem *idItem = new QTableWidgetItem(user.UserID);
        ui->tableWidget->setItem(i, 0, idItem);

        // UserName
        QTableWidgetItem *nameItem = new QTableWidgetItem(user.UserName);
        ui->tableWidget->setItem(i, 1, nameItem);

        // Privilege
        QString privilegeText;
        switch (user.Privilege) {
        case 0: privilegeText = "管理员"; break;
        case 1: privilegeText = "操作员"; break;
        default: privilegeText = QString::number(user.Privilege);
        }
        QTableWidgetItem *privilegeItem = new QTableWidgetItem(privilegeText);
        privilegeItem->setData(Qt::UserRole, user.Privilege); // 保存原始权限值
        ui->tableWidget->setItem(i, 2, privilegeItem);

        // DataCreate
        QTableWidgetItem *dateItem = new QTableWidgetItem(user.DataCreate.toString("yyyy-MM-dd hh:mm:ss"));
        ui->tableWidget->setItem(i, 3, dateItem);

    }

    // 调整列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->label_3->setText(QString("第 %1 页").arg(currentPage));
    int count = infos.size();
    ui->label_5->setText(QString("共 %1 条").arg(count));
    ui->label_4->setText(QString("共 %1 页").arg((count + 10 - 1) / 10));
    qDebug() << "加载了" << infos.size() << "个用户";
}

