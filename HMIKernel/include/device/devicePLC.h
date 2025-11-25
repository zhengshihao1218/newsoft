#ifndef DEVICEPLC_H
#define DEVICEPLC_H
#include <QtNetwork>
#include <QHostAddress>
#include "device.h"
#include "../timer.h"
#include "../hmi_sqlite/tmSQLiteStorage.h"
#include "../hmi_control/curvecontrol.h"

const    int        CONST_REQ_ACTUAL        = 1;    /*即时资料请求*/
const    int        CONST_REQ_READMOTOR     = 2;    /*读资料请求*/
const    int        CONST_REQ_WRITEMOTOR    = 3;    /*写资料请求*/
const    int        CONST_REQ_ALARM         = 4;    /*警报请求*/
const    int        CONST_REQ_CURVE         = 5;    /*曲线请求*/
const    int        CONST_REQ_COMMAND       = 6;    /*命令请求*/
const    int        CONST_REQ_LINESTATUS    = 7;    /*连线请求*/
const    int        CONST_REQ_MOLDSETSTATUS = 8;    /*模具状态请求*/
const    int        CONST_REQ_MOLDSET       = 9;    /*模具资料发送*/
const    int        CONST_REQ_TEMPER        = 10;   /*温度资料请求*/
const    int        CONST_REQ_ADJUST        = 11;   /*校正命令请求*/
const    int        CONST_REQ_ADZERO        = 12;   /*归零命令请求*/

const    int        CONST_REQ_SIEMREAD_DIAG = 13;   /*西门子诊断读*/
const    int        CONST_REQ_SIEMWRITE_DIAG= 14;   /*西门子诊断写*/

const    int        CONST_REQ_PWMTRDATA     = 15;   /*转发电力计资料*/

const    int        CONST_REQ_TRIGGER       = 17;   /*分组触发器资料请求*/
const    int        CONST_REQ_TRIGGER_DATA  = 2018; /*分组触发器资料确认包*/

const    int        CONST_RES_ACTUAL        = 1001; /*即时资料回复*/
const    int        CONST_RES_READMOTOR     = 1002; /*读资料回复*/
const    int        CONST_RES_WRITEMOTOR    = 1003; /*写资料回复*/
const    int        CONST_RES_ALARM         = 1004; /*警报资料回复*/
const    int        CONST_RES_CURVE         = 1005; /*曲线回复*/
const    int        CONST_RES_COMMAND       = 1006; /*命令回复*/
const    int        CONST_RES_LINESTATUS    = 1007; /*连线状态回复*/
const    int        CONST_RES_MOLDSETSTATUS = 1008; /*模具状态回复*/
const    int        CONST_RES_MOLDSET       = 1009; /*模具资料回复*/
const    int        CONST_RES_TEMPER        = 1010; /*温度资料回复*/
const    int        CONST_RES_ADJUST        = 1011; /*校正命令回复*/
const    int        CONST_RES_ADZERO        = 1012; /*归零命令回复*/

const    int        CONST_RES_SIEMREAD_DIAG = 1013; /*西门子读回复*/
const    int        CONST_RES_SIEMWRITE_DIAG= 1014; /*西门子写回复*/

const    int        CONST_RES_PWMTRDATA     = 1015; /*电力计资料回复*/

const    int        CONST_RES_TRIGGER       = 1017; /*分组触发器资料回复*/
const    int        CONST_RES_TRIGGER_DATA  = 1018; /*分组触发器资料发送包*/

#define         PROTOCOL_VER_ERROR          0xFFFF
#define         PROTOCOL_FIRST_ONLINE       0x1
#define         PROTOCOL_MOLDSET_SYNCING    0x2
#define         PROTOCOL_ONLINE_OK          0x3

#define         LINE_STATUS_OK              0
#define         LINE_ERROR_LINESTATUS       0x01
#define         LINE_ERROR_MOLDSET          0x02
#define         LINE_ERROR_ACTUAL           0x04

typedef struct tagTMLINKSTATUS
{
    WORD     wProVer;
    DWORD    dwCycleTime;
    WORD     wPriv;
}TM_LINKSTATUS;

typedef struct tagTMACTVALUE
{
    WORD     wCycleTime;
    QList<QString>    strIDList;
}TM_ACTVALUE;


typedef struct TM_CONDITION
{
    WORD     wType;
    QList<QString>    strParaList;
}TM_CONDITION;

typedef struct tagTMTrigger
{
    QList<TM_CONDITION>    listCondition;
}TM_TRIGGER;

typedef struct tagTMTriggerData
{
    WORD                wReqFlag;
    WORD                wGroupID;
    WORD                wOutTime;
    WORD                wDelayTime;
    WORD                wSendCount;
    WORD                wDataIDFlag;
    QList<TM_TRIGGER>   StartTrigger;
    QList<TM_TRIGGER>   SendTrigger;
    QList<TM_TRIGGER>   StopTrigger;
    QList<QString>      strIDList;
}TM_TRIGGERDATA;

class CtmDevicePLC : public CtmDevice
{
    Q_OBJECT
public:
    CtmDevicePLC(QString strConfig);
    ~CtmDevicePLC();
public:
    int     ReqValues(int nType, int nElements, char* pszIDs[], void* pEx = NULL);
    int     ReqValues(int nType, int nElements, int pIndexs[], void* pEx = NULL);

    int     GetData(char* pdata, int nLen);
    int     SendData(char* pdata, int nLen);

    int     SendMoldSet(int nElements, int pIndexs[]);
    int     GetOnLineStatus();

    int     SetCurveInterval(int nCurveIndex, WORD wMilliSecond);
    WORD    GetCurveInterval(int nCurveIndex);
    void    Run();
private  slots:
    void    slotReceive();

private:
    void    LoadConfig(QString strXmlFile);
    void    InitNet();
    int     GetType(char* pData, int nLen);

    void    ReqTrigerData();

    int     ComposeAndSendData(int nType, int nElements, int pIndexs[], void* pEx);

    int     ComposeDataActual(char* pBuff, TM_ACTVALUE* pActValue);
    int     ComposeDataRead(char* pBuff, int nElements, int pIndexs[]);
    int     ComposeDataWrite(char* pBuff, int nElements, int pIndexs[]);
    int     ComposeDataCommand(char* pBuff, int nElements, int pIndexs[]);
    int     ComposeDataLinkStatus(char* pBuff, TM_LINKSTATUS* pLinkStatus);
    int     ComposeDataMoldsetStatus(char* pBuff, int nNum);
    int     ComposeDataMoldset(char* pBuff, int nElements, int pIndexs[]);
    int     ComposeDataTriggerReq(char* pBuff, TM_TRIGGERDATA* pTriggerData);
    int     ComposeDataTriggerRecv(char* pBuff, int nGroupID);

    int     SetProHeader(char* pBuff);
    int     SetProFooter(char* pBuff);
    int     ComposeTriggerData(char* pOutData, QList<TM_TRIGGER> tmTrigger);

    int     ParseData(char* pBuff, int nLen);
    int     ParseDataLinkStatus(char* pBuff, int nLen);
    int     ParseDataMoldsetStatus(char* pBuff, int nLen);
    int     ParseDataTriggerReq(char* pBuff, int nLen);
    int     ParseDataTriggerRecv(char* pBuff, int nLen);

    int     SetDataToDataBase(char* pData, int nCount, BOOL bSend);
    int     SetTriggerDataToDataBase(char* pData, int nCount, BOOL bSend);
    void    SetCurveData(WORD wCurveNo, char* pData, int nCount, WORD wTriggerType);

    int     WriteTriggerToFile(TM_TRIGGERDATA* pTriggerData);

    TM_TRIGGERDATA* GetTriggetData(WORD wGroupID);


    void    ErrorControl();
    void    Error_Control_PLC(char** pszDBID, DWORD* pdwOldValue, int nDBCount, WORD wErrorType);
    void    Error_Control_Driver();
    void    Error_Control_Axis();

    BOOL    AddErrorLog(tmSQLite_ERROR* pErrorInfo, WORD    wErrorType);
    BOOL    FixErrorLog(tmSQLite_ERROR* pErrorInfo, WORD    wErrorType);


private:
    static CtmDevicePLC*    m_pSelf;
    int                     m_nCounter;
    int                     m_nMaxElements;
    pthread_mutex_t         m_SendMutex;
    QUdpSocket*             m_UdpSocket;

    QString                 m_strConfigfile;
    QString                 m_SrcIP;
    WORD                    m_wSrcPort;
    QString                 m_DestIP;
    WORD                    m_wDestPort;
    QString                 m_ProType;

    BYTE                    m_RxBuffer[4096];                        //    rev buffer
    BYTE                    m_TxBuffer[4096];                        //    send buffer

    TM_LINKSTATUS           m_LinkStatus;
    TM_ACTVALUE             m_ActValue;
    QList<TM_TRIGGERDATA>   m_TriggerList;

    int                     m_nMoldsetNum;
    BOOL                    m_bSendMoldDone;
    BOOL                    m_bActValueDone;

    long                    m_lLineStatusTime;
    long                    m_lCheckOnLineTimer;
    long                    m_lReqMoldsetTime;
    long                    m_lReqTriggerTime;
    long                    m_lAlarmTime;
};


class PLCRxThread: public QThread
{
public:
    explicit PLCRxThread(QString strConfigfile);
    ~PLCRxThread();

protected:
    void run();
private:
    QString                 m_strConfigfile;
};

class PLCTxThread : public QThread
{
public:
    explicit PLCTxThread();
    ~PLCTxThread();
protected:
    void run();
};


#endif // DEVICEPLC_H
