#include "Headers/logmanager.h"
#include <QDir>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

LogManager::LogManager() : db_(nullptr) {
    connectionName_ = "LogManager_Singleton_Connection";
    qDebug() << "LogManager单例创建";
}

LogManager::~LogManager() {
    closeDatabase();
    qDebug() << "LogManager单例销毁";
}

// 单例实现
LogManager& LogManager::getInstance() {
    static LogManager instance;  // 局部静态变量，线程安全
    return instance;
}

bool LogManager::openDatabase() {
    QMutexLocker locker(&mutex_);

    if (db_ && db_->isOpen()) {
        qDebug() << "数据库已经打开";
        return true;
    }

    // 如果连接已存在但未打开，先清理
    if (QSqlDatabase::contains(connectionName_)) {
        QSqlDatabase::removeDatabase(connectionName_);
    }

    db_ = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", connectionName_));
    QString dbPath = "../Database/log/log.db";

    // 处理数据库路径
    QString fullDbPath = dbPath;
    QFileInfo fileInfo(dbPath);
    if (fileInfo.isDir() || fileInfo.suffix().isEmpty()) {
        QDir dir(dbPath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        fullDbPath = dir.filePath("log.db");
    }

    db_->setDatabaseName(fullDbPath);

    if (!db_->open()) {
        qDebug() << "无法打开数据库:" << db_->lastError().text();
        delete db_;
        db_ = nullptr;
        return false;
    }

    qDebug() << "数据库打开成功:" << QDir::toNativeSeparators(fullDbPath);
    return true;
}

bool LogManager::isDatabaseOpen() const {
    return db_ && db_->isOpen();
}

void LogManager::closeDatabase() {
    QMutexLocker locker(&mutex_);
    if (db_) {
        if (db_->isOpen()) {
            // 提交所有未提交的事务
            if (db_->transaction()) {
                db_->commit();
            }
            db_->close();
            qDebug() << "数据库连接已关闭";
        }
        delete db_;
        db_ = nullptr;

        // 移除数据库连接
        QSqlDatabase::removeDatabase(connectionName_);
    }
}

QVector<LogRecord> LogManager::getAllLogs() {
    // QMutexLocker locker(&mutex_);
    qDebug() << "getAllUsers";
    if (db_ && db_->isOpen()) {
        qDebug() << "数据库已经打开";
    }
    QVector<LogRecord> logs;
    QSqlQuery query(*db_);
    query.prepare("SELECT * FROM log_record");
    query.exec();
    while (query.next()) {
        LogRecord log;
        log.No = query.value(0).toInt();
        log.title = query.value(1).toInt();
        log.time = QDateTime::fromString(query.value(2).toString(), "yyyy-MM-dd HH:mm:ss");
        log.UserId = query.value(3).toString();
    }

    return logs;
}

QVector<FullLogRecord> LogManager::getUserLogsWithDetails(const QString& userID, QChar levelFilter, int deviceFilter)
{
    // QMutexLocker locker(&mutex_);
    qDebug() << "getUserLogsWithDetails for user:" << userID
             << "level filter:" << levelFilter
             << "device filter:" << deviceFilter;

    QVector<FullLogRecord> logs;

    if (!db_ || !db_->isOpen()) {
        qDebug() << "数据库未打开";
        return logs;
    }

    // 构建 SQL 查询
    QString sql =
        "SELECT lr.No, lr.title, lr.time, lr.UserId, "
        "ld.level, ld.detail, ld.device "
        "FROM log_record lr "
        "JOIN log_description ld ON lr.title = ld.title "
        "WHERE lr.UserId = ? ";

    QList<QVariant> bindValues;
    bindValues << userID;

    // 添加 level 筛选条件
    if (!levelFilter.isNull() && levelFilter != 'A') {
        if (levelFilter == 'N') {
            // N 级别显示 E 和 N
            sql += "AND ld.level IN ('E', 'N') ";
        } else if (levelFilter == 'E') {
            // E 级别只显示 E
            sql += "AND ld.level = ? ";
            bindValues << QString(levelFilter);
        }
        // A 级别不添加筛选条件，显示全部
    }

    // 添加 device 筛选条件
    if (deviceFilter == -1) {
        return logs;
    } else if (deviceFilter == 1){

    } else {
        sql += "AND ld.device = ? ";
        bindValues << deviceFilter;
    }

    sql += "ORDER BY lr.time DESC";

    QSqlQuery query(*db_);
    query.prepare(sql);

    // 绑定参数
    for (const QVariant& value : bindValues) {
        query.addBindValue(value);
    }

    if (!query.exec()) {
        qDebug() << "联表查询失败:" << query.lastError().text();
        return logs;
    }

    while (query.next()) {
        FullLogRecord log;
        log.No = query.value("No").toInt();
        log.title = query.value("title").toInt();
        log.time = QDateTime::fromString(query.value("time").toString(), "yyyy-MM-dd HH:mm:ss");
        log.UserId = query.value("UserId").toString();
        log.level = query.value("level").toString().at(0);
        log.detail = query.value("detail").toString();
        log.device = query.value("device").toInt();
        logs.append(log);
    }

    qDebug() << "找到" << logs.size() << "条日志记录";
    return logs;
}

// 添加用户，需要添加线程安全锁
int LogManager::addLog(const QString& userID, int title) {

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法添加用户";
        return false;
    }
    QDateTime currentTime = QDateTime::currentDateTime();

    QSqlQuery query(*db_);
    query.prepare("INSERT INTO log_record (title, time, UserId) "
                  "VALUES (?, ?, ?)");

    query.addBindValue(title);
    query.addBindValue(currentTime.toString("yyyy-MM-dd HH:mm:ss"));
    query.addBindValue(userID);

    if (!query.exec()) {
        return 0;
    }

    emit logAdded();
    qDebug() << "log添加成功:" << userID;
    return 1;
}

