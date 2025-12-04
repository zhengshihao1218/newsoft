#include "Headers/newfatiguetestdialog.h"
#include "ui_newfatiguetestdialog.h"

NewFatigueTestDialog::NewFatigueTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewFatigueTestDialog)
{
    ui->setupUi(this);
    initQCustomPlot();
    // int TEST_MOTIONTYPE = GetDBValue("COMP_AXIS1_TEST_MOTIONTYPE").lValue;
    // qDebug() << "TEST_MOTIONTYPE = " << TEST_MOTIONTYPE;
    // int TEST_PREPAREPOSI = GetDBValue("COMP_AXIS1_TEST_PREPAREPOSI").lValue;
    // qDebug() << "TEST_PREPAREPOSI = " << TEST_PREPAREPOSI;
    // int COMP_AXIS1_TEST_STARTPOSI = GetDBValue("COMP_AXIS1_TEST_STARTPOSI").lValue;
    // qDebug() << "COMP_AXIS1_TEST_STARTPOSI = " << COMP_AXIS1_TEST_STARTPOSI;
    // int COMP_AXIS1_TEST_STOPPOSI = GetDBValue("COMP_AXIS1_TEST_STOPPOSI").lValue;
    // qDebug() << "COMP_AXIS1_TEST_STOPPOSI = " << COMP_AXIS1_TEST_STOPPOSI;
    // int COMP_AXIS1_TEST_SUBMOTIONTYPE = GetDBValue("COMP_AXIS1_TEST_SUBMOTIONTYPE").lValue;
    // qDebug() << "COMP_AXIS1_TEST_SUBMOTIONTYPE = " << COMP_AXIS1_TEST_SUBMOTIONTYPE;
}

NewFatigueTestDialog::~NewFatigueTestDialog()
{
    delete ui;
}

void NewFatigueTestDialog::onPlotValueChange()
{
    double A = ui->COMP_AXIS1_TEST_FORMULA_A->value();
    double B = ui->COMP_AXIS1_TEST_FORMULA_B->value();
    double a = ui->COMP_AXIS1_TEST_FORMULA_ALPHA->value();
    double b = ui->COMP_AXIS1_TEST_FORMULA_BETA->value();

    QVector<double> xData, yData;

    // 初始化最小值和最大值
    double yMin = std::numeric_limits<double>::max();  // 初始化为最大值
    double yMax = std::numeric_limits<double>::lowest();  // 初始化为最小值

    // 填充数据并计算最大最小值
    for (double T = -2; T <= 2; T += 0.001) {
        xData.push_back(T);
        double yValue = A * sin(pow(2, a) * M_PI * T) + B * sin(pow(2, b) * M_PI * T);
        yData.push_back(yValue);

        // 更新最小值和最大值
        if (yValue < yMin) {
            yMin = yValue;  // 更新最小值
        }
        if (yValue > yMax) {
            yMax = yValue;  // 更新最大值
        }
    }

    // 更新图表数据
    ui->plotView->graph(0)->setData(xData, yData);

    // 动态设置 Y 轴范围，使其自适应数据
    ui->plotView->yAxis->setRange(yMin - 1, yMax + 1);  // 添加一个小的缓冲，避免图表紧贴边界

    // 重新绘制图表
    ui->plotView->replot();
}

void NewFatigueTestDialog::initQCustomPlot()
{
    ui->plotView->addGraph();
    ui->plotView->graph(0)->setPen(QPen(Qt::blue));  // Set the pen color for the graph

    // Setup the axes
    ui->plotView->xAxis->setLabel("时间 (s)");  // Set x-axis label
    ui->plotView->yAxis->setLabel("振幅 (mm)");  // Set y-axis label

    // Customize the plot appearance
    ui->plotView->xAxis->setRange(-2, 2);  // X-axis range from 0 to 10 (example)
    ui->plotView->yAxis->setRange(-2, 2);  // Y-axis range from -10 to 10 (example)
    ui->plotView->replot();
}


void NewFatigueTestDialog::on_buttonBox_accepted()
{
    // SetDBValue("HMI_DB_TEST_NUMBER1",);
    // int COMP_AXIS1_TEST_FORMULA_BETA = GetDBValue("COMP_AXIS1_TEST_FORMULA_BETA").lValue;
    // qDebug() << "COMP_AXIS1_TEST_FORMULA_BETA 未修改之前是： " << COMP_AXIS1_TEST_FORMULA_BETA;
    // COMP_AXIS1_TEST_FORMULA_BETA = ui->COMP_AXIS1_TEST_FORMULA_BETA->value() * 1000;
    // qDebug() << "COMP_AXIS1_TEST_FORMULA_BETA 即将修改的数值是： " << COMP_AXIS1_TEST_FORMULA_BETA;

    SetDBValue("COMP_AXIS1_TEST_SUBMOTIONTYPE",0);
    SetDBValue("COMP_AXIS1_TEST_FORMULA_A", ui->COMP_AXIS1_TEST_FORMULA_A->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_FORMULA_BETA", ui->COMP_AXIS1_TEST_FORMULA_BETA->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_FORMULA_B", ui->COMP_AXIS1_TEST_FORMULA_B->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_FORMULA_ALPHA", ui->COMP_AXIS1_TEST_FORMULA_ALPHA->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_PLANNUM", ui->COMP_AXIS1_TEST_PLANNUM->value());
    SetDBValue("COMP_AXIS1_TEST_PREPAREPOSI", ui->COMP_AXIS1_TEST_PREPAREPOSI->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_STARTPOSI", ui->COMP_AXIS1_TEST_STARTPOSI->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_SWITCHCOOLTEMPER", ui->COMP_AXIS1_TEST_SWITCHCOOLTEMPER->value() * 1000);
    SetDBValue("COMP_AXIS1_TEST_SWITCHCOOLBACKTEMPER", ui->COMP_AXIS1_TEST_SWITCHCOOLBACKTEMPER->value() * 1000);
    // qDebug() << "COMP_AXIS1_TEST_FORMULA_BETA 修改之后的数值是： " << GetDBValue("COMP_AXIS1_TEST_FORMULA_BETA").lValue;
    this->close();
}


void NewFatigueTestDialog::on_buttonBox_rejected()
{
    this->close();
}


void NewFatigueTestDialog::on_COMP_AXIS1_TEST_FORMULA_A_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_COMP_AXIS1_TEST_FORMULA_B_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_COMP_AXIS1_TEST_FORMULA_ALPHA_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_COMP_AXIS1_TEST_FORMULA_BETA_valueChanged(double arg1)
{
    onPlotValueChange();
}

