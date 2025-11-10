#include "SingleApplication.h"
#include <QWidget>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QFileInfo>
#include <QLibrary>
#include <Windows.h>


SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , bRunning(false)
    , localServer(NULL)
    , mainWindow(NULL)
{
    // 取应用程序名作为LocalServer的名字
    serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    //qDebug()<<serverName;
    initLocalConnection();
}


////////////////////////////////////////////////////////////////////////////////
// 说明：
// 检查是否已經有一个实例在运行, true - 有实例运行， false - 没有实例运行
////////////////////////////////////////////////////////////////////////////////
bool SingleApplication::isRunning()
{
    return bRunning;
}

void SingleApplication::restoreMainWindow()
{
    if (!mainWindow) return;

    mainWindow->raise();
    mainWindow->activateWindow();

    // 恢复最小化窗口
    if (mainWindow->isMinimized()) {
        mainWindow->showNormal();  // 将最小化的窗口恢复为正常状态
    }

    mainWindow->setWindowState((mainWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    mainWindow->show();
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 通过socket通讯实现程序单实例运行，监听到新的连接时触发该函数
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::newLocalConnection() {
    QLocalSocket *socket = localServer->nextPendingConnection();
    if (!socket) return;
    socket->waitForReadyRead(1000);
    QTextStream stream(socket);  // 其他处理
    delete socket;

    if (mainWindow != NULL) {
        mainWindow->raise();  // 将窗口置于最前面
        mainWindow->activateWindow();  // 获取焦点

        // 如果窗口被最小化，恢复窗口
        if (mainWindow->isMinimized()) {
            mainWindow->showNormal();  // 恢复窗口大小
            mainWindow->setWindowState(mainWindow->windowState() & ~Qt::WindowMinimized);  // 去掉最小化状态
        }

        mainWindow->show();

        // 强制将窗口恢复并显示在最前面
        HWND hwnd = (HWND)mainWindow->winId();
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);  // 将窗口置于最前
        ShowWindow(hwnd, SW_RESTORE);  // 恢复最小化窗口
    }
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 通过socket通讯实现程序单实例运行，
// 初始化本地连接，如果连接不上server，则创建，否则退出
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::initLocalConnection()
{
    bRunning = false;
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(500))
    {
        bRunning = true;
        // 其他处理，如：将启动参数发送到服务端
        QTextStream stream(&socket);
        QStringList args = QCoreApplication::arguments();
        if (args.count() > 1)
            stream << args.last();
        else
            stream << QString();
        stream.flush();
        socket.waitForBytesWritten();

        return;
    }

    //连接不上服务器，就创建一个
    newLocalServer();
}

////////////////////////////////////////////////////////////////////////////////
// 说明：
// 创建LocalServer
////////////////////////////////////////////////////////////////////////////////
void SingleApplication::newLocalServer()
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if(!localServer->listen(serverName))
    {
        // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
        if(localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(serverName); // <-- 重点
            localServer->listen(serverName); // 再次监听
        }
    }
}
