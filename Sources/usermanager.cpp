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
    static UserManager instance;  // 局部静态变量，线程安全(C++11及以上)
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

// 其他方法实现保持不变，但需要添加线程安全锁
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
    qDebug() << "getUser 开始了";
    QMutexLocker locker(&mutex_);
    qDebug() << "getUser 通过了锁";
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
