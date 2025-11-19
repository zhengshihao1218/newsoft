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

private:
    Ui::MainWindow *ui;
    QTimer *m_longPressTimer;
    bool m_isLongPress;
    bool m_is2PlotVisiable;
    void permissionSetting(int level);
};
#endif // MAINWINDOW_H
