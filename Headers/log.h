#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QDir>
#include <QCoreApplication>

class Log : public QObject
{
    Q_OBJECT

public:
    // 日志级别
    enum LogLevel {
        DebugLevel   = 0,
        InfoLevel    = 1,
        WarningLevel = 2,
        ErrorLevel   = 3,
        FatalLevel   = 4
    };

    // 获取单例实例
    static Log* instance();

    // 初始化日志系统
    static void init(const QString& fileName = "");

    // 设置日志级别
    static void setLogLevel(LogLevel level);

    // 获取当前日志文件路径
    static QString getLogFilePath();

    // 静态日志函数（方便使用）
    static void debug(const QString& message);
    static void info(const QString& message);
    static void warning(const QString& message);
    static void error(const QString& message);
    static void fatal(const QString& message);

private:
    explicit Log(QObject *parent = nullptr);
    ~Log();

    // 实际写日志的函数
    void writeLog(LogLevel level, const QString& message);

    // Qt消息处理函数
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    static Log* m_instance;      // 单例实例
    static QMutex m_mutex;       // 互斥锁保证线程安全
    static QFile m_logFile;      // 日志文件
    static QTextStream m_stream; // 输出流
    static LogLevel m_logLevel;  // 当前日志级别
    static QString m_filePath;   // 日志文件路径
};

// 使用宏定义简化调用
#define LOG_DEBUG(msg) Log::debug(msg)
#define LOG_INFO(msg)  Log::info(msg)
#define LOG_WARN(msg)  Log::warning(msg)
#define LOG_ERROR(msg) Log::error(msg)
#define LOG_FATAL(msg) Log::fatal(msg)

#endif // LOG_H
