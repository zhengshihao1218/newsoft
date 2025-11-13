#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QCryptographicHash>
#include <QSqlDatabase>
#include <QMutex>
#include <QMutexLocker>

struct UserInfo {
    QString UserID;
    QString Password;
    QString UserName;
    int Privilege;
    QDateTime DataCreate;
};

class UserManager {
public:
    static UserManager& getInstance();
    // 数据库操作
    bool openDatabase();
    void closeDatabase();
    bool isDatabaseOpen() const;

    // 用户管理功能
    // 1 -- 成功
    // 0 -- 失败
    // -1 用户已存在
    int addUser(const QString& userID, const QString& plainPassword,
                const QString& userName, int privilege);
    bool deleteUser(const QString& userID);
    UserInfo getUser(const QString& userID);
    QVector<UserInfo> getAllUsers();
    // 分页获取用户信息
    QVector<UserInfo> getUsersByPage(int page);

    // 获取用户总数（用于计算总页数）
    int getUserCount();

    // 身份验证
    bool authenticate(const QString& userID, const QString& plainPassword);

    // 工具函数
    static QString hashPassword(const QString& password);

private:
    UserManager();  // 私有构造函数
    ~UserManager(); // 私有析构函数



    QSqlDatabase* db_;
    QString connectionName_;
    mutable QMutex mutex_;  // 线程安全
};

#endif // USERMANAGER_H
