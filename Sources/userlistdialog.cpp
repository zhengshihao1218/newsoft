#include "Headers/userlistdialog.h"
#include "ui_userlistdialog.h"

UserListDialog::UserListDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserListDialog)
{
    ui->setupUi(this);
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
    ui->tableWidget->setRowCount(0);
    QVector<UserInfo>infos = UserManager::getInstance().getAllUsers();
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

    qDebug() << "加载了" << infos.size() << "个用户";
}
