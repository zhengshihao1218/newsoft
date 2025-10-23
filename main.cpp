#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qssPath;
    qssPath = ":/qdarkstyle/dark/darkstyle.qss";
    QFile file(qssPath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        qApp->setStyleSheet(stream.readAll());
        file.close();
    } else {
        qDebug() << "无法打开样式表文件:" << qssPath;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
