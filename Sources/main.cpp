#include "Headers/mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QToolTip>
#include <QSystemSemaphore>
#include <QMessageBox>
#include "Headers/singleapplication.h"
#include "HMIKernel/include/global.h"
#include "HMIKernel/include/timer.h"
#include "HMIKernel/include/publicsignal.h"
#include "HMIKernel/include/database/database.h"
#include "HMIKernel/include/device/device.h"
#include "HMIKernel/include/device/devicePLC.h"
#include "HMIKernel/include/hmi_sqlite/tmSQLiteStorage.h"
#include "Headers/log.h"

class ToolTipBlocker : public QObject
{
protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::ToolTip) {
            // 完全拦截 Tooltip 事件
            QToolTip::hideText();
            event->ignore();
            return true;
        }
        return QObject::eventFilter(obj, event);
    }
};

void initHMI()
{
    qDebug()<<"HMI:"<< g_MultiLanguage["ERR_PLC_ERROR11"];
    Init_Timer();
    Init_Msg();

    ///@ init database
    Init_Database("HMI_DB.db");

    //@
    Init_Moldset(2000, "MoldIDList.xml");
    Init_Recordset(2000);
    Init_Alarm(2000);
    Init_User(200);
    Init_DevicePLC("comm.config");

    //@ test database:
    DWORD lid = 0x20000001;
    int n2 = GetDBValue(lid).lValue;
    LOG_DEBUG("Init over: g_pDatabase =" + n2);
    // qDebug() << "Init over: g_pDatabase =" << g_pDatabase << ", n2=" << n2;
}


int main(int argc, char *argv[])
{
    // 使用SingleApplication替换QApplication
    // QApplication a(argc, argv);
    // Log::init();
    SingleApplication a(argc, argv);
    if(!a.isRunning()){
        // 设置样式表
        QString qssPath;
        QSettings settings;
        qDebug() << "保存的主题设置:" << settings.value("Theme/DarkMode").toString();
        QString lightMode = settings.value("Theme/DarkMode","light").toString();
        if(lightMode == "light") {
            qssPath = ":/qdarkstyle/light/lightstyle.qss";
        } else {
            qssPath = ":/qdarkstyle/dark/darkstyle.qss";
        }
        // qssPath = ":/qdarkstyle/dark/darkstyle.qss";
        QFile file(qssPath);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&file);
            qApp->setStyleSheet(stream.readAll());
            file.close();
        } else {
            qDebug() << "无法打开样式表文件:" << qssPath;
        }

        // 安装全局事件过滤器
        ToolTipBlocker *filter = new ToolTipBlocker();
        a.installEventFilter(filter);

        Log::init();
        initHMI();

        MainWindow w;
        // w.show();
        w.showMaximized();
        return a.exec();
    }
    return 0;
}
