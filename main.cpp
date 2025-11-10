#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QToolTip>
#include <QSystemSemaphore>
#include <QMessageBox>
#include "singleapplication.h"

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

int main(int argc, char *argv[])
{
    // 使用SingleApplication替换QApplication
    // QApplication a(argc, argv);
    SingleApplication a(argc, argv);
    if(!a.isRunning()){
        // 设置样式表
        QString qssPath;
        qssPath = ":/qdarkstyle/light/lightstyle.qss";
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

        MainWindow w;
        // w.show();
        w.showMaximized();
        return a.exec();
    }
    return 0;
}
