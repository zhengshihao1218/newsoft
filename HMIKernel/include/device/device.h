#ifndef DEVICE_H
#define DEVICE_H
#include <QThread>
#include "../common.h"
#include "../database/database.h"

#define     DEVICE_MAX              16


#define     ERROR_DATAPATH          -1
#define     ERROR_EXIST             -2
#define     ERROR_DEVICE_FULL       -3

class CtmDevice;

typedef    struct tagDEVICE_MAP
{
    WORD        wDataPath;
    CtmDevice*  pDevice;
} DEVICE_MAP;

class CtmDevice : public QObject
{
    Q_OBJECT
public:
    CtmDevice(QObject *parent = nullptr);
    ~CtmDevice();

    virtual int     ReqValues(int nType, int nElements, char* pszIDs[], void* pEx = NULL)   {return 0;}
    virtual int     ReqValues(int nType, int nElements, int pIndexs[], void* pEx = NULL)    {return 0;}

    virtual int     GetData(void* pdata, int nLen)                                          {return 0;}
    virtual int     SendData(void* pdata, int nLen)                                         {return 0;}

    virtual int     SendMoldSet(int nElements, int pIndexs[])                               {return 0;}
    virtual int     GetOnLineStatus()                                                       {return 0;}

    virtual int     SetCurveInterval(int nCurveIndex, WORD wMilliSecond)                    {return 0;}
    virtual WORD    GetCurveInterval(int nCurveIndex)                                       {return 0;}

    virtual void    Run();
    int             m_nConnectStatus;

public:
    int             AddDevice(WORD wDataPath, CtmDevice* pDevice);
    int             DelDevice(WORD wDataPath);

    static CtmDevice* GetDevice(WORD wDataPath);
    static CtmDevice* GetDevice(QString strDataPath);


private:
    static  DEVICE_MAP deviceMap[DEVICE_MAX];

    static  pthread_mutex_t m_mutex;
};

#endif // DEVICE_H
