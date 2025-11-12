#include "Headers/EtherCatClient.h"
#include <QDebug>

EtherCatClient::EtherCatClient(QObject *parent)
    : QObject(parent),
    socket(new QUdpSocket(this)),
    targetPort(2212)
{
    connect(socket, &QUdpSocket::readyRead, this, &EtherCatClient::onReadyRead);
    connect(socket, &QUdpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError err){
        Q_UNUSED(err)
        emit errorOccurred(socket->errorString());
    });
}

void EtherCatClient::setTarget(const QString &ip, quint16 port)
{
    targetIp = QHostAddress(ip);
    targetPort = port;
}

bool EtherCatClient::connectToTarget()
{
    if (targetIp.isNull()) {
        emit errorOccurred("Target IP not set.");
        return false;
    }

    // UDP逻辑连接（不会真正建立会话）
    socket->connectToHost(targetIp, targetPort);
    if (!socket->waitForConnected(100)) {
        qDebug() << "[EtherCAT] UDP socket logically connected to"
                 << targetIp.toString() << ":" << targetPort;
    }
    return true;
}

void EtherCatClient::sendRawCommand(const QByteArray &data)
{
    if (!socket)
        return;

    qint64 bytes = 0;

    if (socket->state() == QAbstractSocket::ConnectedState)
        bytes = socket->write(data);
    else
        bytes = socket->writeDatagram(data, targetIp, targetPort);

    if (bytes == -1)
        emit errorOccurred(socket->errorString());
    else
        emit packetSent(data);

    qDebug() << "[EtherCAT] Sent" << bytes << "bytes to"
             << targetIp.toString() << ":" << targetPort
             << "Payload:" << data.toHex(' ');
}

void EtherCatClient::onReadyRead()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        emit packetReceived(datagram, sender);

        qDebug() << "[EtherCAT] Received from" << sender.toString()
                 << ":" << senderPort
                 << datagram.toHex(' ');
    }
}

// -------------------- 常用命令 --------------------

void EtherCatClient::sendJogCommand()
{
    // 寸动命令示例（来自Wireshark）
    QByteArray jogCmd = QByteArray::fromHex("160006004b0300000200331200000e0000008866");
    sendRawCommand(jogCmd);
}

void EtherCatClient::sendStopCommand()
{
    // 示例：假设停止命令仅修改命令码
    QByteArray stopCmd = QByteArray::fromHex("160006004b0300000000331200000e0000008866");
    sendRawCommand(stopCmd);
}

void EtherCatClient::sendResetCommand()
{
    // 示例：报警复位命令（假设不同命令码）
    QByteArray resetCmd = QByteArray::fromHex("160006004c0300000000331200000e0000008866");
    sendRawCommand(resetCmd);
}
