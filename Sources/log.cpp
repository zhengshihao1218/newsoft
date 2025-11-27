#include "Headers/Log.h"
#include <iostream>

// 静态成员初始化
Log* Log::m_instance = nullptr;
QMutex Log::m_mutex;
QFile Log::m_logFile;
QTextStream Log::m_stream;
Log::LogLevel Log::m_logLevel = Log::DebugLevel;
QString Log::m_filePath = "";

Log::Log(QObject *parent) : QObject(parent)
{
    // 初始化文本流
    m_stream.setDevice(&m_logFile);
    m_stream.setEncoding(QStringConverter::Utf8);
}

Log::~Log()
{
    if (m_logFile.isOpen()) {
        info("Application exited. Log file closed.");
        m_logFile.close();
    }
}

Log* Log::instance()
{
    if (!m_instance) {
        // QMutexLocker locker(&m_mutex);
        if (!m_instance) {
            m_instance = new Log();
        }
    }
    return m_instance;
}

void Log::init(const QString& fileName)
{
    // QMutexLocker locker(&m_mutex);

    // 如果已经初始化，先关闭之前的文件
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }

    // 确定日志文件名
    if (fileName.isEmpty()) {
        // 默认日志文件名：程序名_日期.log
        QString appName = QCoreApplication::applicationName();
        if (appName.isEmpty()) {
            appName = "Application";
        }
        QString dateStr = QDateTime::currentDateTime().toString("yyyyMMdd");
        m_filePath = QString("%1/log/%2_%3.log")
                         .arg(QCoreApplication::applicationDirPath())
                         .arg(appName)
                         .arg(dateStr);
    } else {
        m_filePath = fileName;
    }

    // 确保目录存在
    QFileInfo fileInfo(m_filePath);
    QDir logDir = fileInfo.absoluteDir();
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }

    // 打开日志文件
    m_logFile.setFileName(m_filePath);
    if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Failed to open log file: " << m_filePath.toStdString() << std::endl;
        return;
    }

    // 安装Qt消息处理函数
    qInstallMessageHandler(messageHandler);

    // 记录启动信息
    QString startMsg = QString("=== Log System Started ===\n"
                               "Application: %1\n"
                               "Version: %2\n"
                               "Log File: %3\n"
                               "Start Time: %4\n")
                           .arg(QCoreApplication::applicationName())
                           .arg(QCoreApplication::applicationVersion())
                           .arg(m_filePath)
                           .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    m_stream << startMsg << "\n";
    m_stream.flush();

    std::cout << "Log system initialized. Log file: " << m_filePath.toStdString() << std::endl;
}

void Log::setLogLevel(LogLevel level)
{
    // QMutexLocker locker(&m_mutex);
    m_logLevel = level;
}

QString Log::getLogFilePath()
{
    return m_filePath;
}

void Log::debug(const QString& message)
{
    instance()->writeLog(DebugLevel, message);
}

void Log::info(const QString& message)
{
    instance()->writeLog(InfoLevel, message);
}

void Log::warning(const QString& message)
{
    instance()->writeLog(WarningLevel, message);
}

void Log::error(const QString& message)
{
    instance()->writeLog(ErrorLevel, message);
}

void Log::fatal(const QString& message)
{
    instance()->writeLog(FatalLevel, message);
}

void Log::writeLog(LogLevel level, const QString& message)
{
    // 检查日志级别
    if (level < m_logLevel) {
        return;
    }

    // QMutexLocker locker(&m_mutex);

    if (!m_logFile.isOpen()) {
        std::cerr << "Log file is not open!" << std::endl;
        return;
    }

    // 获取当前时间
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    // 日志级别字符串
    QString levelStr;
    switch (level) {
    case DebugLevel:   levelStr = "DEBUG"; break;
    case InfoLevel:    levelStr = "INFO"; break;
    case WarningLevel: levelStr = "WARN"; break;
    case ErrorLevel:   levelStr = "ERROR"; break;
    case FatalLevel:   levelStr = "FATAL"; break;
    default:           levelStr = "UNKNOWN"; break;
    }

    // 格式化日志消息
    QString logEntry = QString("[%1] [%2] %3")
                           .arg(timestamp, -23)
                           .arg(levelStr, -7)
                           .arg(message);

    // 写入文件
    m_stream << logEntry << "\n";
    m_stream.flush();

    // 同时在控制台输出（方便调试）
    std::cout << logEntry.toStdString() << std::endl;

    // 如果是致命错误，额外处理
    if (level == FatalLevel) {
        m_stream << "!!! FATAL ERROR - APPLICATION MAY TERMINATE !!!\n";
        m_stream.flush();
    }
}

void Log::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // QMutexLocker locker(&m_mutex);

    if (!m_instance || !m_logFile.isOpen()) {
        // 如果日志系统未初始化，输出到标准错误
        std::cerr << msg.toStdString() << std::endl;
        return;
    }

    // 将Qt消息类型转换为我们的日志级别
    LogLevel level;
    switch (type) {
    case QtDebugMsg:    level = DebugLevel; break;
    case QtInfoMsg:     level = InfoLevel; break;
    case QtWarningMsg:  level = WarningLevel; break;
    case QtCriticalMsg: level = ErrorLevel; break;
    case QtFatalMsg:    level = FatalLevel; break;
    default:            level = InfoLevel; break;
    }

    // 格式化带源码位置的消息（只在Debug级别显示）
    QString formattedMsg = msg;
    if (m_logLevel == DebugLevel) {
        formattedMsg = QString("%1 [%2:%3]").arg(msg).arg(context.file).arg(context.line);
    }

    // 写入日志
    instance()->writeLog(level, formattedMsg);
}
