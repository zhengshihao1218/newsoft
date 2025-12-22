#include "Headers/controlparamentdialog.h"
#include "ui_controlparamentdialog.h"

ControlParamentDialog::ControlParamentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ControlParamentDialog)
{
    ui->setupUi(this);
    tmUpdate = new QTimer(this);
    tmUpdate->start(100);
    connect(tmUpdate, &QTimer::timeout, this, &ControlParamentDialog::updateDBValue);
    on_tabWidget_2_currentChanged(0);
}

ControlParamentDialog::~ControlParamentDialog()
{
    delete ui;
}

void ControlParamentDialog::updateDBValue(){
    ui->label_act_posi->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_POSI").lValue / 1000.0, 'f', 3));
    ui->label_act_pear->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_PRES").lValue / 1000.0, 'f', 3));
    ui->label_act_velo->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_VELO").lValue / 1000.0, 'f', 3));
}

void ControlParamentDialog::on_tabWidget_2_currentChanged(int index)
{
    qDebug() << "on_tabWidget_2_currentChanged index == " << index;
    switch (index) {
    case 0:
        // 工位1位置
        update_tab1_pos_value();
        break;
    case 1:
        // 工位1速度
        break;
    case 2:
        //工位1压力
        break;
    case 3:
        // 工位1力值控制
        break;
    case 4:
        // 工位1试验限值
    default:
        break;
    }

}

// void ControlParamentDialog::refresh(


void ControlParamentDialog::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        // 工位1
        break;
    case 1:
        // 工位2
        break;
    case 2:
        // 试验选项
        break;
    case 3:
        // 驱动器报警
        break;
    case 4:
        //PID管理
        break;
    default:
        break;
    }
}
/**
 * @brief ControlParamentDialog::update_tab1_pos_value
 *
 * 单独获取并显示工位1位置页面的信息
 */
void ControlParamentDialog::update_tab1_pos_value()
{

    qDebug()<< "update_tab1_pos_value";
    byte COMP_AXIS1_PARA_HOMINGMODE = GetDBValue("COMP_AXIS1_PARA_HOMINGMODE").lValue; // 归零模式
    qDebug()<< "归零模式 = " << COMP_AXIS1_PARA_HOMINGMODE;
    if(COMP_AXIS1_PARA_HOMINGMODE == 35){
        ui->comboBox_5->setCurrentIndex(1);
    } else if(COMP_AXIS1_PARA_HOMINGMODE == 0){
        ui->comboBox_5->setCurrentIndex(2);
    } else if(COMP_AXIS1_PARA_HOMINGMODE == 1){
        ui->comboBox_5->setCurrentIndex(0);
    }

    long long COMP_AXIS1_HOMINGPOS = GetDBValue("COMP_AXIS1_HOMINGPOS").lValue; // 归零位置
    ui->doubleSpinBox_5->setValue(COMP_AXIS1_HOMINGPOS / 1000.0);
    long long COMP_AXIS1_PARA_POSIFACTOR = GetDBValue("COMP_AXIS1_PARA_POSIFACTOR").lValue; // 位置系数
    qDebug()<< "位置系数 = " << COMP_AXIS1_PARA_POSIFACTOR;
    ui->doubleSpinBox_6->setValue(COMP_AXIS1_PARA_POSIFACTOR / 1000.0);
    byte COMP_AXIS1_CONF_REVERSEACTPOSITION = GetDBValue("COMP_AXIS1_CONF_REVERSEACTPOSITION").lValue; // 实际位置反向
    ui->comboBox_8->setCurrentIndex(COMP_AXIS1_CONF_REVERSEACTPOSITION);
    byte COMP_AXIS1_LIMIT_POSILIMITOPTION = GetDBValue("COMP_AXIS1_LIMIT_POSILIMITOPTION").lValue; // 位置限定选项
    ui->comboBox_9->setCurrentIndex(COMP_AXIS1_LIMIT_POSILIMITOPTION);
    long long COMP_AXIS1_LIMIT_MINPOSILIMIT = GetDBValue("COMP_AXIS1_LIMIT_MINPOSILIMIT").lValue; // 位置下限
    ui->doubleSpinBox_7->setValue(COMP_AXIS1_LIMIT_MINPOSILIMIT / 1000.0);
    long long COMP_AXIS1_LIMIT_MAXPOSILIMIT = GetDBValue("COMP_AXIS1_LIMIT_MAXPOSILIMIT").lValue; // 位置上限
    ui->doubleSpinBox_8->setValue(COMP_AXIS1_LIMIT_MAXPOSILIMIT / 1000.0);
    long long COMP_AXIS1_PARA_POSIFOLLOWERROR = GetDBValue("COMP_AXIS1_PARA_POSIFOLLOWERROR").lValue; // 位置追随误差
    ui->doubleSpinBox_9->setValue(COMP_AXIS1_PARA_POSIFOLLOWERROR / 1000.0);
    byte COMP_AXIS1_PARA_RESETOPTION = GetDBValue("COMP_AXIS1_PARA_RESETOPTION").lValue; //复位功能
    qDebug()<< "复位功能 = " << COMP_AXIS1_PARA_RESETOPTION;
    ui->comboBox_8->setCurrentIndex(COMP_AXIS1_PARA_RESETOPTION);
    long long COMP_AXIS1_RESETPOSITION = GetDBValue("COMP_AXIS1_RESETPOSITION").lValue; // 复位位置
    ui->doubleSpinBox_10->setValue(COMP_AXIS1_RESETPOSITION / 1000.0);
    qDebug()<< "复位位置 = " << COMP_AXIS1_RESETPOSITION;
    long long COMP_AXIS1_ADJUST_VEL1 = GetDBValue("COMP_AXIS1_ADJUST_VEL1").lValue; // 调机参数1速度
    qDebug()<< "调机参数1速度 获取 = " << COMP_AXIS1_ADJUST_VEL1;
    // float XXX = COMP_AXIS1_ADJUST_VEL1 / 1000;
    // qDebug()<< "调机参数1速度 转成float";
    ui->doubleSpinBox_1_speed->setValue(COMP_AXIS1_ADJUST_VEL1 / 1000.0);
    qDebug()<< "调机参数1速度 设置  ";
    ui->label_266->setText(QString::number(COMP_AXIS1_ADJUST_VEL1 / 1000.0, 'f', 3));
    qDebug()<< "调机参数1速度 = " << COMP_AXIS1_ADJUST_VEL1;
    long long COMP_AXIS1_ADJUST_KP1 = GetDBValue("COMP_AXIS1_ADJUST_KP1").lValue; // 调机参数1 Kp
    float XXX2 = COMP_AXIS1_ADJUST_KP1 / 1000.0;
    ui->doubleSpinBox_186->setValue(XXX2);
    qDebug()<< "Kp = " << COMP_AXIS1_ADJUST_KP1;
    long long COMP_AXIS1_ADJUST_KI1 = GetDBValue("COMP_AXIS1_ADJUST_KI1").lValue; // 调机参数1 Ki
    ui->doubleSpinBox_187->setValue(COMP_AXIS1_ADJUST_KI1 / 1000.0);
    qDebug()<< "Ki = " << COMP_AXIS1_ADJUST_KI1;
    long long COMP_AXIS1_ADJUST_KD1 = GetDBValue("COMP_AXIS1_ADJUST_KD1").lValue; // 调机参数1 Kd
    ui->doubleSpinBox_188->setValue(COMP_AXIS1_ADJUST_KD1 / 1000.0);
    qDebug()<< "COMP_AXIS1_ADJUST_KD1 = " << COMP_AXIS1_ADJUST_KD1;
    long long COMP_AXIS1_ADJUST_VELPREFEEDFACTOR1 = GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR1").lValue; // 调机参数1 速度前馈系数
    ui->doubleSpinBox_189->setValue(COMP_AXIS1_ADJUST_VELPREFEEDFACTOR1 / 1000.0);
    qDebug()<< "速度前馈系数 = " << COMP_AXIS1_ADJUST_VELPREFEEDFACTOR1;
    long long COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR1 = GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR1").lValue; // 调机参数1 加速度前馈系数
    ui->doubleSpinBox_190->setValue(COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR1 / 1000.0);

    /*long long COMP_AXIS1_ADJUST_VEL2 = GetDBValue("COMP_AXIS1_ADJUST_VEL2").lValue;*/ // 调机参数1速度
    // 速度2
    ui->doubleSpinBox_192->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL2").lValue / 1000.0);
    ui->label_267->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL2").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_193->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP2").lValue / 1000.0);
    ui->doubleSpinBox_194->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI2").lValue / 1000.0);
    ui->doubleSpinBox_195->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD2").lValue / 1000.0);
    ui->doubleSpinBox_196->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR2").lValue / 1000.0);
    ui->doubleSpinBox_197->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR2").lValue / 1000.0);

    // 速度3
    ui->doubleSpinBox_199->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL3").lValue / 1000.0);
    ui->label_268->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL3").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_200->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP3").lValue / 1000.0);
    ui->doubleSpinBox_201->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI3").lValue / 1000.0);
    ui->doubleSpinBox_202->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD3").lValue / 1000.0);
    ui->doubleSpinBox_203->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR3").lValue / 1000.0);
    ui->doubleSpinBox_204->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR3").lValue / 1000.0);

    // 速度4
    ui->doubleSpinBox_206->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL4").lValue / 1000.0);
    ui->label_277->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL4").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_207->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP4").lValue / 1000.0);
    ui->doubleSpinBox_208->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI4").lValue / 1000.0);
    ui->doubleSpinBox_209->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD4").lValue / 1000.0);
    ui->doubleSpinBox_210->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR4").lValue / 1000.0);
    ui->doubleSpinBox_211->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR4").lValue / 1000.0);

    // 速度5
    ui->doubleSpinBox_184->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL5").lValue / 1000.0);
    ui->label_278->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL5").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_218->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP5").lValue / 1000.0);
    ui->doubleSpinBox_223->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI5").lValue / 1000.0);
    ui->doubleSpinBox_231->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD5").lValue / 1000.0);
    ui->doubleSpinBox_234->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR5").lValue / 1000.0);
    ui->doubleSpinBox_235->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR5").lValue / 1000.0);

    // 速度6
    ui->doubleSpinBox_191->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL6").lValue / 1000.0);
    ui->label_279->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL6").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_219->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP6").lValue / 1000.0);
    ui->doubleSpinBox_224->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI6").lValue / 1000.0);
    ui->doubleSpinBox_232->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD6").lValue / 1000.0);
    ui->doubleSpinBox_236->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR6").lValue / 1000.0);
    ui->doubleSpinBox_237->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR6").lValue / 1000.0);

    // 速度7
    ui->doubleSpinBox_198->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL7").lValue / 1000.0);
    ui->label_280->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL7").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_220->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP7").lValue / 1000.0);
    ui->doubleSpinBox_225->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI7").lValue / 1000.0);
    ui->doubleSpinBox_233->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD7").lValue / 1000.0);
    ui->doubleSpinBox_238->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR7").lValue / 1000.0);
    ui->doubleSpinBox_239->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR7").lValue / 1000.0);

    // 速度8
    ui->doubleSpinBox_205->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL8").lValue / 1000.0);
    ui->label_281->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL8").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_221->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP8").lValue / 1000.0);
    ui->doubleSpinBox_226->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI8").lValue / 1000.0);
    ui->doubleSpinBox_240->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD8").lValue / 1000.0);
    ui->doubleSpinBox_241->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR8").lValue / 1000.0);
    ui->doubleSpinBox_242->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR8").lValue / 1000.0);

    // 速度9
    ui->doubleSpinBox_212->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL9").lValue / 1000.0);
    ui->label_282->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL9").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_222->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP9").lValue / 1000.0);
    ui->doubleSpinBox_227->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI9").lValue / 1000.0);
    ui->doubleSpinBox_243->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD9").lValue / 1000.0);
    ui->doubleSpinBox_244->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR9").lValue / 1000.0);
    ui->doubleSpinBox_245->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR9").lValue / 1000.0);

    // 速度10
    // ui->doubleSpinBox_213->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL10").lValue / 1000.0);
    // ui->label_283->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL10").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_217->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP10").lValue / 1000.0);
    ui->doubleSpinBox_228->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI10").lValue / 1000.0);
    ui->doubleSpinBox_247->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD10").lValue / 1000.0);
    ui->doubleSpinBox_246->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR10").lValue / 1000.0);
    ui->doubleSpinBox_252->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR10").lValue / 1000.0);

    // 速度11
    // ui->doubleSpinBox_213->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL11").lValue / 1000.0);
    // ui->label_283->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL10").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_217->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP11").lValue / 1000.0);
    ui->doubleSpinBox_228->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI11").lValue / 1000.0);
    ui->doubleSpinBox_247->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD11").lValue / 1000.0);
    ui->doubleSpinBox_246->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR11").lValue / 1000.0);
    ui->doubleSpinBox_252->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR11").lValue / 1000.0);

    // 速度12
    // ui->doubleSpinBox_214->setValue(GetDBValue("COMP_AXIS1_ADJUST_VEL11").lValue / 1000.0);
    // ui->label_283->setText(QString::number(GetDBValue("COMP_AXIS1_ADJUST_VEL10").lValue / 1000.0, 'f', 3));
    ui->doubleSpinBox_215->setValue(GetDBValue("COMP_AXIS1_ADJUST_KP12").lValue / 1000.0);
    ui->doubleSpinBox_230->setValue(GetDBValue("COMP_AXIS1_ADJUST_KI12").lValue / 1000.0);
    ui->doubleSpinBox_249->setValue(GetDBValue("COMP_AXIS1_ADJUST_KD12").lValue / 1000.0);
    ui->doubleSpinBox_251->setValue(GetDBValue("COMP_AXIS1_ADJUST_VELPREFEEDFACTOR12").lValue / 1000.0);
    ui->doubleSpinBox_254->setValue(GetDBValue("COMP_AXIS1_ADJUST_ACCPREFEEDFACTOR12").lValue / 1000.0);
}

void ControlParamentDialog::on_doubleSpinBox_185_valueChanged(double arg1)
{
    if (arg1 > 0) {
        if (arg1 < ui->doubleSpinBox_192->value()){
            ui->label_266->setText(QString::number(arg1));
        } else {
            ui->doubleSpinBox_1_speed->setValue(ui->doubleSpinBox_192->value() - 0.01);
            // ui->label_266->setValue(ui->doubleSpinBox_192->value() - 0.01);
             ui->label_266->setText(QString::number(ui->doubleSpinBox_192->value() - 0.01));
        }
    } else {
        ui->doubleSpinBox_1_speed->setValue(0.01);
        ui->label_266->setText(QString::number(0.01));
    }
}

