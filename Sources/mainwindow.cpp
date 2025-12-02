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
    // 初始化日志

    // 测试中文日志
    LOG_INFO("测试中文日志 - Chinese log test");
    LOG_DEBUG("这是一个调试信息");
    // 初始化HMIKernel流程
    initHMIKernel();
    LOG_DEBUG("HMIKernel 初始化完成");
    // 屏蔽所有 toolbar 的右键菜单
    initToolBar();
    // 没有登录，把大多数Action都设置成置灰的
    initNotLoginAction();
    initPlotView();
    // 为工具栏安装事件过滤器
    designUpAction();
    designDownAction();
    designMotorAction();
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
    tmUpdate = new QTimer(this);
    tmUpdate->start(100);
    connect(tmUpdate, &QTimer::timeout, this, &MainWindow::updateDBValue);
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

void MainWindow::designMotorAction()
{
    // 找到up_action对应的QToolButton
    QToolButton *motor_start_stop_Button = nullptr;
    QList<QToolButton*> toolButtons = ui->toolBar->findChildren<QToolButton*>();

    for (QToolButton *button : toolButtons) {
        if (button->defaultAction() == ui->motor_start_stop_action) {
            motor_start_stop_Button = button;
            break;
        }
    }

    if (motor_start_stop_Button) {
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

        motor_start_stop_Button->setStyleSheet(style);

        // 连接释放信号
        connect(motor_start_stop_Button, &QToolButton::released, this, [this]() {
            if(MainWindow::sendCmdToPlc(0xffff,false)){
                qDebug() << "up_action释放";
            }
        });

    }
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
            MainWindow::sendCmdToPlc(14,false);
            qDebug() << "up_action按下";
            QIcon pressedIcon(":/images/images/up_run.png");
            ui->up_action->setIcon(pressedIcon);
            m_longPressTimer->start();
        });

        // 连接释放信号
        connect(upButton, &QToolButton::released, this, [this]() {
            MainWindow::sendCmdToPlc(0xffff,false); // 释放触发边沿
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
            MainWindow::sendCmdToPlc(15,false);
            qDebug() << "down_action按下";
            QIcon pressedIcon(":/images/images/down_run.png");
            ui->down_action->setIcon(pressedIcon);

            m_longPressTimer->start();
        });

        // 连接释放信号
        connect(downButton, &QToolButton::released, this, [this]() {
            MainWindow::sendCmdToPlc(0xffff,false); // 释放触发边沿
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
    initHMIKernel();
    long long db1 = GetDBValue("MCHN_CONFIG_DEVICE1").lValue;
    qDebug() << "当前MCHN_CONFIG_DEVICE1为" << db1;
    long long db2 = GetDBValue("MCHN_CONFIG_AXIS_DRIVER1").lValue;
    qDebug() << "当前MCHN_CONFIG_AXIS_DRIVER1为" << db2;

    SetDBValue("MCHN_CONFIG_ACTAXISGROUP",1); //设置当前轴为主轴
    if (checked){
        //         if(MainWindow::sendCmdToPlc(0xffff,false)){
        //             qDebug() << "up_action释放";
        //         }
        // MainWindow::sendCmdToPlc(12,false);
        // MainWindow::sendCmdToPlc(0xffff,false);
        // LOG_DEBUG("启动马达");

        long long db = GetDBValue("MCHN_CONFIG_ACTAXISGROUP").lValue;
        qDebug() << "当前操作轴为" << db;
        if(MainWindow::sendCmdToPlc(12,false)){
            LOG_DEBUG("启动马达");
        }; // 启动马达
        // ui->motor_info->setPixmap(QPixmap(":/images/images/motor_on.png"));
    } else {
        if(MainWindow::sendCmdToPlc(2,false)){
            LOG_DEBUG("关闭马达");
        }; // 启动马达
         // ui->motor_info->setPixmap(QPixmap(":/images/images/motor_off.png"));
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

void MainWindow::initHMIKernel()
{
    // qDebug()<<"HMI:"<< g_MultiLanguage["ERR_PLC_ERROR11"];
    // Init_Timer();
    // Init_Msg();

    // ///@ init database
    // Init_Database("HMI_DB.db");

    // //@
    // Init_Moldset(2000, "MoldIDList.xml");
    // Init_Recordset(2000);
    // Init_Alarm(2000);
    // Init_User(200);
    // Init_DevicePLC("comm.config");

    //@ test database:
    DWORD lid = 0x20000001;
    int n2 = GetDBValue(lid).lValue;
    LOG_DEBUG("Init over: g_pDatabase =" + n2);
    // qDebug() << "Init over: g_pDatabase =" << g_pDatabase << ", n2=" << n2;

    // 轴组配置 专门是适配动力单元的！！！！
    BYTE nType = 0;//设备类型
    // 0//无
    //     1//IO卡          此设备为1
    //     2//驱动器          此设备为3个
    //     3//压力传感器
    //     4//驱动器菲仕

    nType = 1;
    BYTE nCount = 1;//设备个数
    BYTE nConf = ((1<<4)+1);//IO卡          此设备为1
    WORD LLLL = -1;
    LLLL = SetDBValue("MCHN_CONFIG_DEVICE1", nConf);//设备类型序号（ECAT设备）
    qDebug() << "initHMI SetDBValue === " << LLLL;
    long long QQQQ = -1;
    QQQQ = GetDBValue("MCHN_CONFIG_DEVICE1").lValue;
    WORD ZZZ = GetDBValue("MCHN_CONFIG_DEVICE1").wPrecision;
    qDebug() << "QQQQ = " <<QQQQ << "ZZZ = " << ZZZ;
    nType = 2;
    nCount = 3;//设备个数
    nConf = ((nType<<4)+nCount);//驱动器          此设备为3个
    // QString config_1 = QString("MCHN_CONFIG_DEVICE%1").arg(2), nConf;
    SetDBValue("MCHN_CONFIG_DEVICE2", nConf);//设备类型序号（ECAT设备）

    nType = 2;
    nCount = 3;//设备个数
    nConf = ((nType<<4)+nCount);//驱动器          此设备为3个
    SetDBValue("MCHN_CONFIG_DEVICE3", nConf);//设备类型序号（ECAT设备）

    BYTE nConf2 = 5;//轴组组合（轴bit组合成轴组）0X5
    SetDBValue("MCHN_CONFIG_AXIS_GROUP1", nConf2);

    BYTE nConf3 = 6  ;//轴1 所连驱动器----> 0x6
    SetDBValue("MCHN_CONFIG_AXIS_DRIVER1", nConf3);

    BYTE nConf4 = 48 ;  //轴3  所连驱动器---> 0x30
    SetDBValue("MCHN_CONFIG_AXIS_DRIVER3", nConf4);

}

void MainWindow::updateDBValue()
{
    CtmDevice *device =CtmDevice::GetDevice("PLC");//获取PLC设备
    if(device == NULL)return;
    int nstatu = device->GetOnLineStatus();
    bool isOn = (nstatu== 0);
    if(!isOn){
        ui->error_info_2->setText("未连接");
        // qDebug() << "PLCwei is off line: statu=" << nstatu;
        return;
    }else{
        ui->error_info_2->setText("连接成功");
        // qDebug() << "Get value fv =" << fv;
    }
    // long long n1 = GetDBValue("CTRL_MOTORSTATE1").lValue;
    // qDebug() << "马达1状态 获取 n1 " <<  n1;
    // long long n2 = GetDBValue("COMP_AXIS1_ACTUAL_PRES").lValue;
    // qDebug() << "马达1状态 获取 n2 " <<  n2;
    // long long n3 = GetDBValue("COMP_AXIS1_ACTUAL_POSI").lValue;
    // qDebug() << "马达1状态 获取 n3 " <<  n3;

    if(GetDBValue("CTRL_MOTORSTATE1").lValue == 0){
        ui->motor_start_stop_action->setChecked(false);
        ui->motor_info->setPixmap(QPixmap(":/images/images/motor_on.png"));
    } else {
        ui->motor_start_stop_action->setChecked(true);
        ui->motor_info->setPixmap(QPixmap(":/images/images/motor_off.png"));
    }
    ui->label_sensor_posi->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_POSI").lValue));
    ui->label_sensor_pear->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_PRES").lValue));
    ui->label_sensor_velo->setText(QString::number(GetDBValue("COMP_AXIS1_ACTUAL_VELO").lValue));
}

bool MainWindow::sendCmdToPlc(int nKey, bool isHelpAxis){
    int pCmd = nKey;
    int nTmp = 0;
    CtmDevice *device = CtmDevice::GetDevice("PLC");
    if (device == NULL) return false;
    device->ReqValues(CONST_REQ_COMMAND,1,&pCmd,NULL);
    return true;
}
