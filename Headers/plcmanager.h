#ifndef PLCMANAGER_H
#define PLCMANAGER_H

#include <QObject>
#include "Include/device/device.h"
#include "Include/device/devicePLC.h"

class PLCManager
{
public:
    PLCManager();
    ~PLCManager();
    void connectPLC();
};

#endif // PLCMANAGER_H
