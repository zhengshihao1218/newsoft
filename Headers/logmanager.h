#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <QString>
#include <QChar>
#include <QVector>
#include <QDateTime>
#include <QSqlDatabase>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>

struct LogDescription {
    int title;
    QChar level;
    QString detail;
    int device;
};

struct LogRecord {
    int No;
    int title;
    QDateTime time;
    QString UserId;
};

struct FullLogRecord {
    int No;
    int title;
    QDateTime time;
    QString UserId;
    QChar level;
    QString detail;
    int device;
};

class LogManager : public QObject
{
    Q_OBJECT

public:
    // LogManager();
    static LogManager& getInstance();
    // 数据库操作
    bool openDatabase();
    void closeDatabase();
    bool isDatabaseOpen() const;
    QVector<LogRecord> getAllLogs();
    // 增加log
    // 1 -- 成功
    // 0 -- 失败
    // -1 用户已存在
    int addLog(const QString& userID, int title);
    // 获取用户完整日志信息（带筛选功能）
    QVector<FullLogRecord> getUserLogsWithDetails(const QString& userID, QChar levelFilter = QChar(), int deviceFilter = -1);

signals:
    void logAdded();  // 新增日志信号

private:
    LogManager();
    ~LogManager();
    QSqlDatabase* db_;
    QString connectionName_;
    mutable QMutex mutex_;
};

#endif // LOGMANAGER_H
