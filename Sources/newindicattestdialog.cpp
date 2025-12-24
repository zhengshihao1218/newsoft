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

    ui->HMI_DB_TEST_NUMBER1->setText(textNumber);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->HMI_DB_TEST_CREATEDATE1->setText(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

NewIndicatTestDialog::~NewIndicatTestDialog()
{
    delete ui;
}

void NewIndicatTestDialog::on_buttonBox_accepted()
{
    if(ui->COMP_AXIS1_TEST_PREPAREPOSI->value() == 0){
        ui->error_info->setText("准备位置不能为0");
        return;
    }
    if(ui->COMP_AXIS1_TEST_STARTPOSI->value() == 0) {
        ui->error_info->setText("起始位置不能是0");
        return;
    }
    if(ui->COMP_AXIS1_TEST_STOPPOSI->value() == 0) {
        ui->error_info->setText("结束位置不能是0");
        return;
    }
    if(ui->HMI_DB_TEST_PRODUCT_SN1->text() == "" || ui->HMI_DB_TEST_PRODUCT_SN1->text().isEmpty()){
        ui->error_info->setText("试件编号不能为空");
        return;
    }
    if(ui->HMI_DB_TEST_NUMBER1->text() == "" || ui->HMI_DB_TEST_NUMBER1->text().isEmpty()){
        ui->error_info->setText("试验编号不能为空");
        return;
    }
    // 先把每个速度的选择都设置关闭，以免之前开着的项目被保留下来
    for (int i = 1; i <= 15; i++) {
        char key[100];
        snprintf(key, sizeof(key), "COMP_AXIS1_TEST_TABLE_WT%d_OPTION", i);
        SetDBValue(key, 0);
    }
    // 再开始设置试验参数
    SetDBValue("COMP_AXIS1_TEST_MOTIONTYPE",2); // 试验类型是示功试验
    SetDBString("HMI_DB_TEST_NUMBER1",ui->HMI_DB_TEST_NUMBER1->text().toUtf8().data(),strlen(ui->HMI_DB_TEST_NUMBER1->text().toUtf8().data()));
    SetDBString("HMI_DB_TEST_CREATEDATE1",ui->HMI_DB_TEST_CREATEDATE1->text().toUtf8().data(),strlen(ui->HMI_DB_TEST_CREATEDATE1->text().toUtf8().data()));
    SetDBString("HMI_DB_TEST_PRODUCT_SN1",ui->HMI_DB_TEST_PRODUCT_SN1->text().toUtf8().data(),strlen(ui->HMI_DB_TEST_PRODUCT_SN1->text().toUtf8().data()));
    long long  COMP_AXIS1_TEST_PREPAREPOSI = ui->COMP_AXIS1_TEST_PREPAREPOSI->value();
    qDebug() << "UI COMP_AXIS1_TEST_PREPAREPOSI = " << COMP_AXIS1_TEST_PREPAREPOSI;
    long long COMP_AXIS1_TEST_PREPAREPOSI_res = COMP_AXIS1_TEST_PREPAREPOSI * 1000;

    SetDBValue("COMP_AXIS1_TEST_PREPAREPOSI", COMP_AXIS1_TEST_PREPAREPOSI_res);
    int COMP_AXIS1_TEST_STARTPOSI = ui->COMP_AXIS1_TEST_STARTPOSI->value();
    SetDBValue("COMP_AXIS1_TEST_STARTPOSI",  COMP_AXIS1_TEST_STARTPOSI * 1000);
    SetDBValue("COMP_AXIS1_TEST_STOPPOSI", ui->COMP_AXIS1_TEST_STOPPOSI->value() * 1000);
    if(ui->COMP_AXIS1_TEST_TABLE_WT1_OPTION->isChecked()){
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT1_OPTION",1);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT1_VEL",ui->COMP_AXIS1_TEST_TABLE_WT1_VEL->value() * 1000);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT1_TIMES",ui->COMP_AXIS1_TEST_TABLE_WT1_TIMES->value());
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT1_POS1", (COMP_AXIS1_TEST_STARTPOSI - ui->doubleSpinBox_34->value()) * 1000 );
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT1_POS2", (COMP_AXIS1_TEST_STARTPOSI + ui->doubleSpinBox_34->value()) * 1000 );
    }

    if(ui->COMP_AXIS1_TEST_TABLE_WT2_OPTION->isChecked()){
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT2_OPTION",1);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT2_VEL",ui->COMP_AXIS1_TEST_TABLE_WT2_VEL->value() * 1000);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT2_TIMES",ui->COMP_AXIS1_TEST_TABLE_WT2_TIMES->value());
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT2_POS1", (COMP_AXIS1_TEST_STARTPOSI - ui->doubleSpinBox_41->value()) * 1000 );
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT2_POS2", (COMP_AXIS1_TEST_STARTPOSI + ui->doubleSpinBox_41->value()) * 1000 );
    }

    if(ui->COMP_AXIS1_TEST_TABLE_WT3_OPTION->isChecked()){
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT3_OPTION",1);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT3_VEL",ui->COMP_AXIS1_TEST_TABLE_WT3_VEL->value() * 1000);
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT3_TIMES",ui->COMP_AXIS1_TEST_TABLE_WT3_TIMES->value());
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT3_POS1", (COMP_AXIS1_TEST_STARTPOSI - ui->doubleSpinBox_48->value()) * 1000 );
        SetDBValue("COMP_AXIS1_TEST_TABLE_WT3_POS2", (COMP_AXIS1_TEST_STARTPOSI + ui->doubleSpinBox_48->value()) * 1000 );
    }
    if(ui->comboBox->currentIndex() == 0){
        SetDBValue("HMI_DB_TEST_AXIS1_FCABANDONOPTION",0);
    }
    newTestComp();
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

double NewIndicatTestDialog::calculate_frequency_from_velocity_amplitude(double velocity_mps, double amplitude_mm) {
    // 将毫米转换为米
    double amplitude_m = amplitude_mm / 1000.0;

    // 计算频率: f = v / (2π * A)
    double frequency = velocity_mps / (2 * M_PI * amplitude_m);

    return frequency;
}

void NewIndicatTestDialog::on_COMP_AXIS1_TEST_TABLE_WT1_VEL_valueChanged(double arg1)
{
    if(arg1 != 0 && ui->doubleSpinBox_34->value() != 0){
        double HZ = calculate_frequency_from_velocity_amplitude(arg1, ui->doubleSpinBox_34->value());
        ui->label_1_HZ->setText(QString::number(HZ, 'f', 2));
    }
}


void NewIndicatTestDialog::on_doubleSpinBox_34_valueChanged(double arg1)
{
    if(ui->COMP_AXIS1_TEST_TABLE_WT1_VEL->value() != 0 && arg1 != 0){
        double HZ = calculate_frequency_from_velocity_amplitude(ui->COMP_AXIS1_TEST_TABLE_WT1_VEL->value(), arg1);
        ui->label_1_HZ->setText(QString::number(HZ, 'f', 2));
    }
}


void NewIndicatTestDialog::on_COMP_AXIS1_TEST_TABLE_WT2_VEL_valueChanged(double arg1)
{
    if(ui->doubleSpinBox_41->value() != 0 && arg1 != 0){
        double HZ = calculate_frequency_from_velocity_amplitude(arg1,  ui->doubleSpinBox_41->value());
        ui->label_2_HZ->setText(QString::number(HZ, 'f', 2));
    }
}


void NewIndicatTestDialog::on_doubleSpinBox_41_valueChanged(double arg1)
{
    if(arg1 != 0 && ui->COMP_AXIS1_TEST_TABLE_WT2_VEL->value()!=0){
        double HZ = calculate_frequency_from_velocity_amplitude(ui->COMP_AXIS1_TEST_TABLE_WT2_VEL->value(), arg1);
        ui->label_2_HZ->setText(QString::number(HZ, 'f', 2));
    }
}


void NewIndicatTestDialog::on_COMP_AXIS1_TEST_TABLE_WT3_VEL_valueChanged(double arg1)
{
    if(arg1 != 0 && ui->doubleSpinBox_48->value() != 0){
        double HZ = calculate_frequency_from_velocity_amplitude(arg1, ui->doubleSpinBox_48->value());
        ui->label_3_HZ->setText(QString::number(HZ, 'f', 2));
    }
}


void NewIndicatTestDialog::on_doubleSpinBox_48_valueChanged(double arg1)
{
    if(arg1 != 0 && ui->COMP_AXIS1_TEST_TABLE_WT3_VEL->value() != 0){
        double HZ = calculate_frequency_from_velocity_amplitude(ui->COMP_AXIS1_TEST_TABLE_WT3_VEL->value(), arg1);
        ui->label_3_HZ->setText(QString::number(HZ, 'f', 2));
    }
}

