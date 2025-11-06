#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_longPressTimer(nullptr)
    , m_isLongPress(false)
{
    ui->setupUi(this);
    // 屏蔽所有 toolbar 的右键菜单
    initToolBar();
    // 没有登录，把大多数Action都设置成置灰的
    initNotLoginAction();
    initPlotView();
    // 为工具栏安装事件过滤器
    designUpAction();
    designDownAction();
    ui->lcdNumber_count->setDigitCount(6);
    ui->lcdNumber_count->display("NULL");
    ui->lcdNumber_time->setDigitCount(9);
    QTime currentTime = QTime::currentTime();
    QString text = QString("%1:%2:%3")
                       .arg(currentTime.hour(), 2, 10, QChar('0'))    // 小时，2位，用0填充
                       .arg(currentTime.minute(), 2, 10, QChar('0'))  // 分钟，2位，用0填充
                       .arg(currentTime.second(), 2, 10, QChar('0')); // 秒，2位，用0填充

    ui->lcdNumber_time->display(text);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_up_clicked()
{

}


void MainWindow::on_pushButton_down_clicked()
{

}


void MainWindow::on_actionwire_triggered()
{

}


void MainWindow::on_motor_start_stop_action_toggled(bool arg1)
{
    // ui->motor_start_stop_action->setChecked(!ui->motor_start_stop_action->isChecked());
}

void MainWindow::initToolBar()
{
    const QList<QToolBar *> toolBars = findChildren<QToolBar *>();
    for (QToolBar *bar : toolBars) {
        bar->setContextMenuPolicy(Qt::PreventContextMenu);
    }
}

void MainWindow::initNotLoginAction()
{
    ui->new_user_action->setEnabled(false);
    ui->system_parment_action->setEnabled(false);
    // ui->up_action->setEnabled(false);
    // ui->down_action->setEnabled(false);
    // ui->actionuser_list_action->setEnabled(false);
    ui->motor_start_stop_action->setEnabled(false);
    ui->clear_error_action->setEnabled(false);
    ui->prepare_experiment_action->setEnabled(false);
    ui->browse_experiment_action->setEnabled(false);
    ui->start_experiment_action->setEnabled(false);
    ui->control_parment_action->setEnabled(false);
    ui->current_experiment->setEnabled(false);
    ui->stop_experiment_action->setEnabled(false);
    ui->new_experiment_action->setEnabled(false);
    ui->logout_action->setEnabled(false);
    ui->user_list_action->setEnabled(false);
}

void MainWindow::initLoginAction()
{
    ui->new_user_action->setEnabled(true);
    ui->system_parment_action->setEnabled(true);
    // ui->up_action->setEnabled(true);
    // ui->down_action->setEnabled(true);
    // ui->actionuser_list_action->setEnabled(false);
    ui->motor_start_stop_action->setEnabled(true);
    ui->clear_error_action->setEnabled(true);
    ui->prepare_experiment_action->setEnabled(true);
    ui->browse_experiment_action->setEnabled(true);
    ui->start_experiment_action->setEnabled(true);
    ui->control_parment_action->setEnabled(true);
    ui->current_experiment->setEnabled(true);
    ui->stop_experiment_action->setEnabled(true);
    ui->new_experiment_action->setEnabled(true);
    ui->logout_action->setEnabled(true);
    ui->user_list_action->setEnabled(true);
}



void MainWindow::on_login_action_triggered()
{
    LoginDialog *loginDialog = new LoginDialog();
    loginDialog->setWindowFlag(Qt::WindowCloseButtonHint);
    connect(loginDialog, &LoginDialog::login, this, &MainWindow::initLoginAction);
    loginDialog->exec();
    delete loginDialog;
    loginDialog = nullptr;
}


void MainWindow::on_quit_action_triggered()
{
    ExitDialog *exitDialog = new ExitDialog();
    exitDialog->setWindowFlag(Qt::WindowCloseButtonHint);
    exitDialog->exec();
    delete exitDialog;
    exitDialog = nullptr;
}


void MainWindow::on_system_parment_action_triggered()
{
    SystemParameterDialog *systemParameterDialog = new SystemParameterDialog();
    systemParameterDialog->setWindowFlag(Qt::WindowCloseButtonHint);
    systemParameterDialog->exec();
    delete systemParameterDialog;
    systemParameterDialog = nullptr;
}


void MainWindow::on_new_experiment_action_triggered()
{
    NewExperimentDialog *dialog = new NewExperimentDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}

void MainWindow::initPlotView()
{
    ui->plotView->addGraph();
    ui->plotView->setBackground(QPixmap(":/images/images/back.png"));
}

void MainWindow::onUpShortClick()
{

}

void MainWindow::onUpLongPress()
{

}

void MainWindow::onDownShortClick()
{

}

void MainWindow::onDownLongPress()
{

}

void MainWindow::designUpAction()
{
    // 找到up_action对应的QToolButton
    QToolButton *upButton = nullptr;
    QList<QToolButton*> toolButtons = ui->toolBar->findChildren<QToolButton*>();

    for (QToolButton *button : toolButtons) {
        if (button->defaultAction() == ui->up_action) {
            upButton = button;
            break;
        }
    }

    if (upButton) {
        qDebug() << "找到up_action对应的QToolButton";
        QString style =
            "QToolBar QToolButton  {"
            "    border: none;"
            "    padding: 4px;"
            "    border-radius: 6px;"
            "    transition: all 0.15s;"
            "}"
            "QToolBar QToolButton:hover {"
            "    padding: 4px;"  // 悬停时padding为0
            "}"
            "QToolBar QToolButton:pressed {"
            "    padding: 4px;"  // 按下时padding为0
            "}";

        upButton->setStyleSheet(style);
        // 创建长按计时器
        m_longPressTimer = new QTimer(this);
        m_longPressTimer->setSingleShot(true);
        m_longPressTimer->setInterval(800);
        m_isLongPress = false;

        // 连接按下信号
        connect(upButton, &QToolButton::pressed, this, [this]() {
            qDebug() << "up_action按下";
            QIcon pressedIcon(":/images/images/up_run.png");
            ui->up_action->setIcon(pressedIcon);
            m_longPressTimer->start();
        });

        // 连接释放信号
        connect(upButton, &QToolButton::released, this, [this]() {
            qDebug() << "up_action释放";
            QIcon normalIcon(":/images/images/up.png");
            ui->up_action->setIcon(normalIcon);

            m_longPressTimer->stop();

            if (!m_isLongPress) {
                qDebug() << "短按触发";
                onUpShortClick();
            }
            m_isLongPress = false;
        });

        // 长按超时
        connect(m_longPressTimer, &QTimer::timeout, this, [this]() {
            qDebug() << "长按触发";
            m_isLongPress = true;
            onUpLongPress();
        });
    }
}

void MainWindow::designDownAction()
{
    // 找到up_action对应的QToolButton
    QToolButton *downButton = nullptr;
    QList<QToolButton*> toolButtons = ui->toolBar->findChildren<QToolButton*>();

    for (QToolButton *button : toolButtons) {
        if (button->defaultAction() == ui->down_action) {
            downButton = button;
            break;
        }
    }

    if (downButton) {
        qDebug() << "找到down_action对应的QToolButton";
        qDebug() << "找到up_action对应的QToolButton";
        QString style =
            "QToolBar QToolButton  {"
            "    border: none;"
            "    padding: 4px;"
            "    border-radius: 6px;"
            "    transition: all 0.15s;"
            "}"
            "QToolBar QToolButton:hover {"
            "    padding: 4px;"  // 悬停时padding为0
            "}"
            "QToolBar QToolButton:pressed {"
            "    padding: 4px;"  // 按下时padding为0
            "}";

        downButton->setStyleSheet(style);

        // 创建长按计时器
        m_longPressTimer = new QTimer(this);
        m_longPressTimer->setSingleShot(true);
        m_longPressTimer->setInterval(800);
        m_isLongPress = false;

        // 连接按下信号
        connect(downButton, &QToolButton::pressed, this, [this]() {
            qDebug() << "down_action按下";
            QIcon pressedIcon(":/images/images/down_run.png");
            ui->down_action->setIcon(pressedIcon);
            m_longPressTimer->start();
        });

        // 连接释放信号
        connect(downButton, &QToolButton::released, this, [this]() {
            qDebug() << "down_action释放";
            QIcon normalIcon(":/images/images/down.png");
            ui->down_action->setIcon(normalIcon);

            m_longPressTimer->stop();

            if (!m_isLongPress) {
                qDebug() << "短按触发";
                onDownShortClick();
            }
            m_isLongPress = false;
        });

        // 长按超时
        connect(m_longPressTimer, &QTimer::timeout, this, [this]() {
            qDebug() << "长按触发";
            m_isLongPress = true;
            onDownLongPress();
        });
    }
}


void MainWindow::on_motor_start_stop_action_triggered(bool checked)
{
    ui->up_action->setEnabled(checked);
    ui->down_action->setEnabled(checked);
    ui->prepare_experiment_action->setEnabled(checked);
    ui->start_experiment_action->setEnabled(checked);
    if (checked){
        ui->motor_info->setPixmap(QPixmap(":/images/images/motor_on.png"));
    } else {
         ui->motor_info->setPixmap(QPixmap(":/images/images/motor_off.png"));
    }
}


void MainWindow::on_logout_action_triggered()
{
    LogoutDialog *dialog = new LogoutDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);\
    connect(dialog, &LogoutDialog::logout, this, &MainWindow::initNotLoginAction);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_new_user_action_triggered()
{
    AddUserDialog *dialog = new AddUserDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_user_list_action_triggered()
{
    UserListDialog *dialog = new UserListDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_about_action_triggered()
{
    AboutDialog *dialog = new AboutDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}

