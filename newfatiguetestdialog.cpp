#include "newfatiguetestdialog.h"
#include "ui_newfatiguetestdialog.h"

NewFatigueTestDialog::NewFatigueTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewFatigueTestDialog)
{
    ui->setupUi(this);
    initQCustomPlot();
}

NewFatigueTestDialog::~NewFatigueTestDialog()
{
    delete ui;
}



void NewFatigueTestDialog::on_A1_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_B1_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_a1_valueChanged(double arg1)
{
    onPlotValueChange();
}


void NewFatigueTestDialog::on_b1_valueChanged(double arg1)
{
    onPlotValueChange();
}

void NewFatigueTestDialog::onPlotValueChange()
{
    double A = ui->A1->value();
    double B = ui->B1->value();
    double a = ui->a1->value();
    double b = ui->b1->value();

    QVector<double> xData, yData;

    // 初始化最小值和最大值
    double yMin = std::numeric_limits<double>::max();  // 初始化为最大值
    double yMax = std::numeric_limits<double>::lowest();  // 初始化为最小值

    // 填充数据并计算最大最小值
    for (double T = -2; T <= 2; T += 0.01) {
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
    this->close();
}


void NewFatigueTestDialog::on_buttonBox_rejected()
{
    this->close();
}

