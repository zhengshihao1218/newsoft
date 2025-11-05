#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "exitdialog.h"
#include "systemparameterdialog.h"
#include "newexperimentdialog.h"

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
    void initLoginAction();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
