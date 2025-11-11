#ifndef ETHERCATCLIENT_H
#define ETHERCATCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QTimer>

/**
 * @brief EtherCAT-over-UDP 通信类
 * 支持发送控制命令（如寸动、停止、复位）给 EtherCAT 设备（如伺服驱动器）
 */
class EtherCatClient : public QObject
{
    Q_OBJECT
public:
    explicit EtherCatClient(QObject *parent = nullptr);

    // 设置目标设备地址和端口
    void setTarget(const QString &ip, quint16 port = 2212);

    // 连接（UDP逻辑绑定，不是真正握手）
    bool connectToTarget();

    // 常用命令
    void sendJogCommand();     // 电机寸动
    void sendStopCommand();    // 电机停止
    void sendResetCommand();   // 报警复位

signals:
    void packetSent(const QByteArray &data);
    void packetReceived(const QByteArray &data, const QHostAddress &sender);
    void errorOccurred(const QString &message);

private slots:
    void onReadyRead();

private:
    void sendRawCommand(const QByteArray &data);

    QUdpSocket *socket;
    QHostAddress targetIp;
    quint16 targetPort;
};

#endif // ETHERCATCLIENT_H
