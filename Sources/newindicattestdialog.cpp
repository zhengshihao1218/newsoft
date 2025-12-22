#include "Headers/newindicattestdialog.h"
#include "ui_newindicattestdialog.h"

NewIndicatTestDialog::NewIndicatTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewIndicatTestDialog)
{
    ui->setupUi(this);
    ui->widget_4->setVisible(false);
    ui->widget_5->setVisible(false);
    ui->widget_6->setVisible(false);
    ui->widget_7->setVisible(false);
    ui->widget_8->setVisible(false);
    ui->widget_9->setVisible(false);
    ui->widget_10->setVisible(false);
    ui->widget_11->setVisible(false);
    ui->widget_12->setVisible(false);
    ui->widget_13->setVisible(false);
    ui->widget_14->setVisible(false);
    ui->widget_15->setVisible(false);
    current_speed_count = 3;

    char result[50];  // 假设最大长度为100
    QString strResult = "";
    WORD res = GetDBString("HMI_DB_TEST_NUMBER1", result, sizeof(result) - 1);

    if (res == 0) {
        // 成功获取数据，使用 result 进行后续操作
        strResult = QString::fromUtf8(result);
        qDebug() << "获取到的测试编号：" << strResult;
    } else {
        // 获取失败
        qDebug() << "获取数据失败";
    }
    QString textNumber = NewIndicatTestDialog::incrementStringSuffix(strResult);

    ui->lineEdit->setText(textNumber);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->lineEdit_3->setText(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

NewIndicatTestDialog::~NewIndicatTestDialog()
{
    delete ui;
}

void NewIndicatTestDialog::on_buttonBox_accepted()
{
    SetDBValue("COMP_AXIS1_TEST_SUBMOTIONTYPE",2);
    this->close();
}


void NewIndicatTestDialog::on_buttonBox_rejected()
{
    this->close();
}

// current_speed_count = 3;
void NewIndicatTestDialog::on_pushButton_clicked()
{
    if(current_speed_count < 15) {
        current_speed_count++;

        // 创建widget指针数组，注意索引对齐
        QWidget* widgets[] = {
            nullptr, // 索引0不用
            nullptr, // 索引1不用
            nullptr, // 索引2不用
            nullptr, // 索引3不用
            ui->widget_4,
            ui->widget_5,
            ui->widget_6,
            ui->widget_7,
            ui->widget_8,
            ui->widget_9,
            ui->widget_10,
            ui->widget_11,
            ui->widget_12,
            ui->widget_13,
            ui->widget_14,
            ui->widget_15
        };

        if(current_speed_count >= 4 && current_speed_count <= 15) {
            widgets[current_speed_count]->setVisible(true);
        }
    }
}

QString NewIndicatTestDialog::incrementStringSuffix(const QString& input)
{
    QRegularExpression re("(.*?)(\\d+)$");
    QRegularExpressionMatch match = re.match(input);

    if (!match.hasMatch()) {
        // 如果没有数字后缀，直接添加"1"
        return input + "1";
    }

    QString prefix = match.captured(1);
    QString numberStr = match.captured(2);

    int number = numberStr.toInt();
    number++;

    // 保持相同长度的前导零
    QString newNumberStr = QString::number(number);

    // 如果新数字比原数字长（如 99 -> 100），不使用前导零
    if (newNumberStr.length() > numberStr.length()) {
        return prefix + newNumberStr;
    }

    // 否则保留前导零
    newNumberStr = newNumberStr.rightJustified(numberStr.length(), '0');
    return prefix + newNumberStr;
}
