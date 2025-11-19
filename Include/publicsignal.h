#ifndef PUBLICSIGNAL_H
#define PUBLICSIGNAL_H

#include <QObject>


class PublicSignal : public QObject
{
    Q_OBJECT
public:
    explicit PublicSignal(QObject *parent = nullptr);

public:
    void SendMsg(unsigned long ulMsg, unsigned long ulP1, unsigned long ulP2, QObject* p);

signals:
    void sigMsg(unsigned long ulMsg, unsigned long ulP1, unsigned long ulP2, QObject* p);
};

#endif // PUBLICSIGNAL_H
