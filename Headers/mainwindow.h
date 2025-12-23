#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "exitdialog.h"
#include "systemparameterdialog.h"
#include "newexperimentdialog.h"
#include "adduserdialog.h"
#include "logoutdialog.h"
#include "userlistdialog.h"
#include "aboutdialog.h"
#include "browseexperimentdialog.h"
#include "controlparamentdialog.h"
#include "usermanager.h"
#include "change_pasword_dialog.h"
#include "logmanager.h"
#include "HMIKernel/include/global.h"
#include "HMIKernel/include/device/device.h"
#include "HMIKernel/include/device/devicePLC.h"
#include "HMIKernel/include/hmi_control/curvecontrol.h"
#include "Headers/log.h"
#include "Headers/qcustomplot.h"

// 所有轴命令
const int CMD_KEY_NONE = 0;              // 无
const int CMD_KEY_ALL_MANUAL = 1;        // 清错
const int CMD_KEY_ALL_MOTOROFF = 2;      // 关闭马达
const int CMD_KEY_ALL_STOP = 3;          // 停止试验

// 当前轴命令
const int CMD_KEY_AXIS_MANUAL = 11;      // 手动清错
const int CMD_KEY_AXIS_MOTOR = 12;       // 马达启停
const int CMD_KEY_AXIS_HOMING = 13;      // 归零
const int CMD_KEY_AXIS_JOGFWD = 14;      // 寸动前进
const int CMD_KEY_AXIS_JOGBWD = 15;      // 寸动后退
const int CMD_KEY_AXIS_START = 16;       // 启动试验
const int CMD_KEY_AXIS_STOP = 17;        // 停止试验
const int CMD_KEY_AXIS_PREPARE = 18;     // 准备试验
const int CMD_KEY_AXIS_GET_FCPRESS = 19; // 获取充气力
const int CMD_KEY_LOCKMOTOR_FWD = 20;    // 悬臂正转
const int CMD_KEY_LOCKMOTOR_BWD = 21;    // 悬臂反转

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initLoginAction(QString id);

protected:

private slots:
    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_actionwire_triggered();

    void on_motor_start_stop_action_toggled(bool arg1);

    void initToolBar();

    void on_login_action_triggered();

    void on_quit_action_triggered();

    void on_system_parment_action_triggered();

    void initNotLoginAction();

    void on_new_experiment_action_triggered();

    void initPlotView();

    void designUpAction();

    void designDownAction();

    void designMotorAction();

    void onUpShortClick();
    void onUpLongPress();
    void onDownShortClick();
    void onDownLongPress();

    void on_motor_start_stop_action_triggered(bool checked);

    void on_logout_action_triggered();

    void on_user_list_action_triggered();

    void on_about_action_triggered();

    void on_browse_experiment_action_triggered();

    void on_current_experiment_triggered();

    void on_control_parment_action_triggered();

    void on_info_view_action_triggered(bool checked);

    void on_tool_view_action_triggered(bool checked);

    void on_two_chart_action_triggered(bool checked);

    void on_dark_light_action_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_change_password_action_triggered();

    void on_log_hmi_radio_toggled(bool checked);

    void on_log_plc_radio_toggled(bool checked);

    void refreshLogView();

    void on_log_e_button_clicked(bool checked);

    void on_log_n_button_clicked(bool checked);

    void on_log_a_button_clicked(bool checked);

    void on_translate_action_triggered(bool checked);

    void on_prepare_experiment_action_triggered();

    void on_start_experiment_action_triggered();

    void on_stop_experiment_action_triggered();

    void on_clear_error_action_triggered();

    void on_reset_action_triggered();

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *m_longPressTimer;
    QTimer* tmUpdate;
    QTimer* plotUpdate;
    bool m_isLongPress;
    bool m_is2PlotVisiable;
    bool m_isPos_raido_check = false;
    bool m_isForce_raido_check = false;
    bool m_isTemp_radio_check = false;
    void permissionSetting(int level);
    QTranslator *m_englishTranslator;
    QTranslator *m_chineseTranslator;
    void initHMIKernel();
    void updateDBValue();
    void updatePlotValue();
    bool sendCmdToPlc(int nKey, bool isHelpAxis);
    void newFatigueTest();
    void newIndicatTest();
    void onLegendClick(QCPLegend *legend,
                                   QCPAbstractLegendItem *item,
                                   QMouseEvent *event);
};
#endif // MAINWINDOW_H
