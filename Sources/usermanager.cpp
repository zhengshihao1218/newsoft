#include "Headers/UserManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

UserManager::UserManager() : db_(nullptr) {
    connectionName_ = "UserManager_Singleton_Connection";
    qDebug() << "UserManager单例创建";
}

UserManager::~UserManager() {
    closeDatabase();
    qDebug() << "UserManager单例销毁";
}

// 单例实现
UserManager& UserManager::getInstance() {
    static UserManager instance;  // 局部静态变量，线程安全
    return instance;
}

bool UserManager::openDatabase() {
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
    QString dbPath = "../Database/user/user.db";

    // 处理数据库路径
    QString fullDbPath = dbPath;
    QFileInfo fileInfo(dbPath);
    if (fileInfo.isDir() || fileInfo.suffix().isEmpty()) {
        QDir dir(dbPath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        fullDbPath = dir.filePath("user.db");
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

// 添加用户，需要添加线程安全锁
int UserManager::addUser(const QString& userID, const QString& plainPassword,
                          const QString& userName, int privilege) {
    QMutexLocker locker(&mutex_);

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法添加用户";
        return false;
    }
    QString hashedPassword = hashPassword(plainPassword);
    QDateTime currentTime = QDateTime::currentDateTime();

    QSqlQuery query(*db_);
    query.prepare("INSERT INTO UserInfo (UserID, Password, UserName, Privilege, DataCreate) "
                  "VALUES (?, ?, ?, ?, ?)");

    query.addBindValue(userID);
    query.addBindValue(hashedPassword);
    query.addBindValue(userName);
    query.addBindValue(privilege);
    query.addBindValue(currentTime.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "添加用户失败:" << query.lastError().text();
        if (query.lastError().text() == "UNIQUE constraint failed: UserInfo.UserID Unable to fetch row")
        {
            return -1;
        }else {
            return 0;
        }
    }

    qDebug() << "用户添加成功:" << userID;
    return 1;
}

// 其他方法类似，都需要添加 QMutexLocker locker(&mutex_);

// 获取用户信息
UserInfo UserManager::getUser(const QString& userID) {
    QMutexLocker locker(&mutex_);
    UserInfo user;

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法获取用户信息";
        return user;
    }

    QSqlQuery query(*db_);
    query.prepare("SELECT UserID, Password, UserName, Privilege, DataCreate FROM UserInfo WHERE UserID = ?");
    query.addBindValue(userID);

    if (query.exec() && query.next()) {
        user.UserID = query.value(0).toString();
        user.Password = query.value(1).toString();
        user.UserName = query.value(2).toString();
        user.Privilege = query.value(3).toInt();
        user.DataCreate = QDateTime::fromString(query.value(4).toString(), "yyyy-MM-dd HH:mm:ss");
        qDebug() << "找到用户:" << userID;
    } else {
        qDebug() << "未找到用户:" << userID;
    }

    return user;
}

// 身份验证
bool UserManager::authenticate(const QString& userID, const QString& plainPassword) {
    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法验证身份";
        return false;
    }

    QString hashedInput = hashPassword(plainPassword);
    qDebug() << "hash算完了";
    UserInfo user = getUser(userID);
    qDebug() << "getUser成功了";
    if (user.UserID.isEmpty()) {
        qDebug() << "用户不存在:" << userID;
        return false;
    }

    bool authenticated = (user.Password == hashedInput);
    qDebug() << "用户" << userID << "身份验证:" << (authenticated ? "成功" : "失败");

    return authenticated;
}

QString UserManager::hashPassword(const QString& password) {
    qDebug() << "hashPassword";
    QByteArray passwordData = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
    qDebug() << "hashPassword2";
    return QString(hash.toHex());
}

bool UserManager::isDatabaseOpen() const {
    return db_ && db_->isOpen();
}

void UserManager::closeDatabase() {
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

QVector<UserInfo> UserManager::getAllUsers() {
    QMutexLocker locker(&mutex_);
    qDebug() << "getAllUsers";
    if (db_ && db_->isOpen()) {
        qDebug() << "数据库已经打开";
    }
    QVector<UserInfo> users;
    QSqlQuery query(*db_);
    query.prepare("SELECT * FROM UserInfo");
    query.exec();
    while (query.next()) {
        UserInfo user;
        user.UserID = query.value(0).toString();
        user.Password = query.value(1).toString();
        user.UserName = query.value(2).toString();
        user.Privilege = query.value(3).toInt();
        user.DataCreate = QDateTime::fromString(query.value(4).toString(), "yyyy-MM-dd HH:mm:ss");
        users.append(user);
    }

    return users;
}

// 获取用户总数
int UserManager::getUserCount() {
    QMutexLocker locker(&mutex_);

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法获取用户数量";
        return 0;
    }

    QSqlQuery query(*db_);
    QString sql = "SELECT COUNT(*) FROM UserInfo";

    if (!query.exec(sql)) {
        qDebug() << "获取用户数量失败:" << query.lastError().text();
        return 0;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "用户总数:" << count;
        return count;
    }

    return 0;
}

// 分页获取用户信息
QVector<UserInfo> UserManager::getUsersByPage(int page) {
    QMutexLocker locker(&mutex_);

    QVector<UserInfo> users;

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开";
        return users;
    }

    int pageSize = 10;

    // 计算偏移量
    int offset = (page - 1) * pageSize;
    if (offset < 0) offset = 0;

    QSqlQuery query(*db_);

    // 使用 LIMIT 和 OFFSET 实现分页
    QString sql = "SELECT UserID, Password, UserName, Privilege, DataCreate "
                  "FROM UserInfo "
                  "ORDER BY DataCreate DESC "  // 按创建时间倒序排列
                  "LIMIT :pageSize OFFSET :offset";

    query.prepare(sql);
    query.bindValue(":pageSize", pageSize);
    query.bindValue(":offset", offset);

    if (!query.exec()) {
        qDebug() << "分页查询失败:" << query.lastError().text();
        qDebug() << "SQL:" << sql;
        qDebug() << "参数: pageSize=" << pageSize << ", offset=" << offset;
        return users;
    }

    int count = 0;
    while (query.next()) {
        count++;
        UserInfo user;
        user.UserID = query.value("UserID").toString();
        user.Password = query.value("Password").toString();
        user.UserName = query.value("UserName").toString();
        user.Privilege = query.value("Privilege").toInt();

        QString dateStr = query.value("DataCreate").toString();
        user.DataCreate = QDateTime::fromString(dateStr, "yyyy-MM-dd HH:mm:ss");
        if (!user.DataCreate.isValid()) {
            user.DataCreate = QDateTime::currentDateTime();
        }

        users.append(user);

        qDebug() << "分页用户" << count << ":" << user.UserID << user.UserName;
    }

    qDebug() << "分页查询成功，获取到" << users.size() << "条记录";
    return users;
}
