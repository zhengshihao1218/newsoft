#include "Headers/mainwindow.h"
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
    m_is2PlotVisiable = false;
    ui->plotView2->setVisible(false);

    QTime currentTime = QTime::currentTime();
    QString text = QString("%1:%2:%3")
                       .arg(currentTime.hour(), 2, 10, QChar('0'))    // 小时，2位，用0填充
                       .arg(currentTime.minute(), 2, 10, QChar('0'))  // 分钟，2位，用0填充
                       .arg(currentTime.second(), 2, 10, QChar('0')); // 秒，2位，用0填充

    ui->lcdNumber_time->display(text);
    permissionSetting(1);
    // 连接数据库
    UserManager::getInstance().openDatabase();
    LogManager::getInstance().openDatabase();
    connect(&LogManager::getInstance(), &LogManager::logAdded,
            this, &MainWindow::refreshLogView);
    // 预加载两个翻译文件
    // m_englishTranslator->load(":/translation/res/newsoft_en_001.qm");
    // m_chineseTranslator->load(":/translation/res/newsoft_zh_CN.qm");
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
    // for (QToolBar *bar : toolBars) {
    //     bar->setContextMenuPolicy(Qt::PreventContextMenu);
    // }
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
    // ui->login_action->setVisible(true);
    ui->login_action->setEnabled(true);
    ui->login_action->setText("用户登录");
    ui->logout_action->setVisible(false);
    ui->change_password_action->setVisible(false);
    permissionSetting(1);
    LogManager::getInstance().addLog(UserManager::getInstance().login_User_ID,5);
    UserManager::getInstance().login_User_ID = "";
}

void MainWindow::initLoginAction(QString id)
{
    // ui->menu_6->setTitle("用户 "+UserManager::getInstance().getUser(id).UserName + " 已登录");
    ui->new_user_action->setEnabled(true);
    ui->system_parment_action->setEnabled(true);
    // ui->up_action->setEnabled(true);
    // ui->down_action->setEnabled(true);
    // ui->actionuser_list_action->setEnabled(false);
    ui->clear_error_action->setEnabled(true);
    // ui->prepare_experiment_action->setEnabled(true);
    ui->browse_experiment_action->setEnabled(true);
    // ui->start_experiment_action->setEnabled(true);
    ui->control_parment_action->setEnabled(true);
    ui->current_experiment->setEnabled(true);
    ui->stop_experiment_action->setEnabled(true);
    ui->new_experiment_action->setEnabled(true);
    ui->logout_action->setEnabled(true);
    ui->user_list_action->setEnabled(true);
    // ui->login_action->setVisible(false);
    ui->login_action->setEnabled(false);
    ui->login_action->setText(UserManager::getInstance().getUser(id).UserName);
    ui->logout_action->setVisible(true);
    ui->motor_start_stop_action->setEnabled(true);
    if(ui->motor_start_stop_action->isChecked()){
        ui->prepare_experiment_action->setEnabled(true);
        ui->start_experiment_action->setEnabled(true);
    }
    ui->change_password_action->setVisible(true);
    permissionSetting(UserManager::getInstance().getUser(id).Privilege);
    UserManager::getInstance().login_User_ID = id;
    LogManager::getInstance().addLog(id,1);
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


void MainWindow::on_browse_experiment_action_triggered()
{
    BrowseExperimentDialog *dialog = new BrowseExperimentDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_current_experiment_triggered()
{
    NewFatigueTestDialog *dialog = new NewFatigueTestDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_control_parment_action_triggered()
{
    ControlParamentDialog *dialog = new ControlParamentDialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}


void MainWindow::on_info_view_action_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}


void MainWindow::on_tool_view_action_triggered(bool checked)
{
    ui->toolBar->setVisible(checked);
}


void MainWindow::on_two_chart_action_triggered(bool checked)
{
    ui->plotView2->setVisible(checked);
}


void MainWindow::on_dark_light_action_triggered(bool checked)
{
    QString qssPath;

    if (checked) {
        qssPath = ":/qdarkstyle/dark/darkstyle.qss";
        qDebug() << "应用暗色主题";
    } else {
        qssPath = ":/qdarkstyle/light/lightstyle.qss";
        qDebug() << "应用亮色主题";
    }

    QFile file(qssPath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        file.close();

        // 应用样式表
        qApp->setStyleSheet(styleSheet);

        // 保存主题设置
        QSettings settings;
        if(checked){
            settings.setValue("Theme/DarkMode", "dark");
        } else {
             settings.setValue("Theme/DarkMode", "light");
        }
        qDebug() << "保存的主题设置:" << settings.value("Theme/DarkMode").toString();
        settings.sync();

    } else {
        qDebug() << "无法打开样式表文件:" << qssPath;
        // 恢复之前的选中状态
        ui->dark_light_action->setChecked(!checked);
        QMessageBox::warning(this, "主题切换失败", "无法加载主题文件，请检查资源文件。");
    }
}

void MainWindow::permissionSetting(int level)
{
    switch (level) {
    case 0:
        ui->menu_3->setEnabled(true);
        ui->system_parment_action->setVisible(true);
        ui->control_parment_action->setVisible(true);
        ui->user_list_action->setVisible(true);
        break;
    case 1:
    default:
        ui->system_parment_action->setVisible(false);
        ui->control_parment_action->setVisible(false);
        ui->user_list_action->setVisible(false);
        ui->menu_3->setEnabled(false);
        break;
    }
}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->info_view_action->setChecked(visible);
}

void MainWindow::on_change_password_action_triggered()
{
    Change_Pasword_Dialog *dialog = new Change_Pasword_Dialog();
    dialog->setWindowFlag(Qt::WindowCloseButtonHint);
    dialog->exec();
    delete dialog;
    dialog = nullptr;
}

void MainWindow::refreshLogView()
{
    // ui->log_a_button->isChecked();
    // ui->log_e_button->isChecked();
    // ui->log_n_button->isChecked();
    // ui->log_hmi_radio->isChecked();
    // ui->log_plc_radio->isChecked();
    QChar level = 'N';
    if (ui->log_n_button->isChecked()) {
        level = 'N';
    }
    if (ui->log_e_button->isChecked()) {
        level = 'E';
    }
    if (ui->log_a_button->isChecked()) {
        level = 'A';
    }
    int device = 1;
    bool hmi_checked = ui->log_hmi_radio->isChecked();
    bool plc_checked = ui->log_plc_radio->isChecked();
    if(hmi_checked && plc_checked) {
        device = 1;
    } else if (hmi_checked && !plc_checked) {
        device = 1000;
    } else if (!hmi_checked && plc_checked) {
        device = 100;
    } else {
        device = -1;
    }

    qDebug() << "refreshLogView " << level << "  device " << device;
    ui->log_table->setRowCount(0);
    QVector<FullLogRecord>logs = LogManager::getInstance().getUserLogsWithDetails(UserManager::getInstance().login_User_ID,level, device);
    ui->log_table->setRowCount(logs.size());
    for (int i = 0; i < logs.size(); ++i) {
        const FullLogRecord &log = logs[i];

        // time
        QTableWidgetItem *timeItem = new QTableWidgetItem(log.time.toString("yyyy-MM-dd hh:mm:ss"));
        ui->log_table->setItem(i, 0, timeItem);

        // level
        QTableWidgetItem *levelItem = new QTableWidgetItem(log.level);
        ui->log_table->setItem(i, 1, levelItem);

        // UserName
        QTableWidgetItem *detailItem = new QTableWidgetItem(log.detail);
        ui->log_table->setItem(i, 2, detailItem);

    }

    // 调整列宽
    //ui->log_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::on_log_hmi_radio_toggled(bool checked)
{
    refreshLogView();
}


void MainWindow::on_log_plc_radio_toggled(bool checked)
{
    refreshLogView();
}



void MainWindow::on_log_e_button_clicked(bool checked)
{
    if(checked){
        ui->log_a_button->setChecked(!checked);
        ui->log_n_button->setChecked(!checked);
        refreshLogView();
    } else {
        ui->log_e_button->setChecked(true);
    }
}


void MainWindow::on_log_n_button_clicked(bool checked)
{
    if(checked) {
        ui->log_a_button->setChecked(!checked);
        ui->log_e_button->setChecked(!checked);
        refreshLogView();
    } else {
        ui->log_n_button->setChecked(true);
    }
}


void MainWindow::on_log_a_button_clicked(bool checked)
{
    if(checked) {
        ui->log_n_button->setChecked(!checked);
        ui->log_e_button->setChecked(!checked);
        refreshLogView();
    } else {
        ui->log_a_button->setChecked(true);
    }
}


void MainWindow::on_translate_action_triggered(bool checked)
{
    // QApplication::removeTranslator(m_englishTranslator);
    // QApplication::removeTranslator(m_chineseTranslator);
    QTranslator translator;
    QString qm_path = "";
    if (checked) {
        qm_path = QApplication::applicationDirPath()+"/Translations/newsoft_en_001.qm";
    } else {
        qm_path = QApplication::applicationDirPath()+"/Translations/newsoft_zh_CN.qm";
    }
    bool b_value = translator.load(qm_path);
    qDebug() << "加载文件 " << qm_path;
    qApp->installTranslator(&translator);
    this->ui->retranslateUi(this);
}

