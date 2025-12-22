#ifndef CONTROLPARAMENTDIALOG_H
#define CONTROLPARAMENTDIALOG_H

#include <QDialog>
#include <QTimer>
#include "HMIKernel/include/global.h"

namespace Ui {
class ControlParamentDialog;
}

class ControlParamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlParamentDialog(QWidget *parent = nullptr);
    ~ControlParamentDialog();

private slots:
    void on_tabWidget_2_currentChanged(int index);

    void on_tabWidget_currentChanged(int index);

    void on_doubleSpinBox_185_valueChanged(double arg1);

private:
    Ui::ControlParamentDialog *ui;
    QTimer* tmUpdate;
    // 实时获取轴1实际数据
    void updateDBValue();
    // 单独获取并显示工位1位置页面的信息
    void update_tab1_pos_value();
};

#endif // CONTROLPARAMENTDIALOG_H
