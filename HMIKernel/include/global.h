#ifndef GLOBAL_H
#define GLOBAL_H
#include "common.h"
#include "publicsignal.h"
#include "database/cblock.h"
#include "device/device.h"
#include "hmi_control/curvecontrol.h"
#include "font/multilanguage.h"
#include "tmmsg.h"

bool        ExistFile(char* pszFileName);
bool        mkMutiDir(const QString path);

BOOL        TestBit (DWORD dwFlag, WORD wIndex);
void        SendMsg(unsigned long ulMsg, unsigned long ulP1, unsigned long ulP2, QObject* p);
void        Trim(char* pszDes, char* pszSrc,  int nLength);
WORD        CRC16(WORD wCrc, char *pData, int nLen);
DWORD       CRC32(char *pData, int nLen);
DWORD       CRC32(char *filename);
int         GetDecimalPowerVal(WORD wNPower);
long        Power(int nBase, int n);
void		StringToHex(char* psz,long* pData);
WORD        CheckSum(WORD *data,WORD len);
void        GetDate(tmDATE* pdate);
void        GetTime(tmTIME* ptime);
void        GetInitialPassword(char* pcMachineID, char* pcPassword,tmDATE dtMachineDateOut, WORD wSystem);
int         GetStageInstall(char* pcPassword, char* pcMachineID, tmDATE dtStartStage, BYTE cStages, WORD wSystem);
void        GetAccDate(tmDATE* pSDate, int nAccDays, tmDATE* pEDate);

BOOL        CheckTimeOut_Install();
WORD        StartUp_Install(char* pcPassword);
WORD		JudgeFactoryOnWork_Install();
void		SaveOperation();
void		DealOperation(OPERATION* pOperation, int nWRflag);
int         ReadOperationFromSRAM(OPERATION* pOperation);
int         WriteOperationToSRAM(OPERATION* pOperation);
void        DealOperationStartMachine();
WORD		CountOperationCRC();
WORD		VER2HEX();
void		SaveCurrentRTCTime(OPERATION* pOperation);

WORD        CvtDate(char* pszDate, char cSeparator, tmDATE date);
WORD        CvtDate(tmDATE date);
WORD        CvtTime(char* pszTime, char cSeparator, tmTIME* ptime);

void        tmMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
QString     GetHMIKernelVersion();


bool        Init_Msg();
bool        Init_Database(QString strDbPath);
bool        Init_Moldset(int nMaxNum, QString strMoldIDList);
bool        Init_Recordset(int nMaxNum);
bool        Init_Alarm(int nMaxNum);
bool        Init_User(int nMaxNum);
bool        Init_DevicePLC(QString strCommuConfig);
bool        Init_Font(QString strXmlPath);


extern  PublicSignal*   g_pPublicSignal;
extern  CtmBlock*       g_pBlock;
extern  CtmMultiLanguage g_MultiLanguage;




#endif // GLOBAL_H
