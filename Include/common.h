#ifndef COMMON_H
#define COMMON_H
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <qdebug.h>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <minwindef.h>
#include <QCryptographicHash>
#include <QtCore/qxmlstream.h>
#include <QDomDocument>
#include <QMutex>
#include <Windows.h>

#define     TYPE_UNKNOWN    0
#define     TYPE_BOOL       1
#define     TYPE_BYTE       2
#define     TYPE_WORD       3
#define     TYPE_DWORD      4
#define     TYPE_CHAR       5
#define     TYPE_SHORT      6
#define     TYPE_INT        7
#define     TYPE_FLOAT      8
#define     TYPE_DOUBLE     9
#define     TYPE_STRING     10

#define     TRUE            1
#define     FALSE           0


#define     DATA_PATH      "./Data/"

#define     PLC_COMMAND_KEYTYPE         0x1233;

#define     ERROR_TYPE_ERROE            1
#define     ERROR_TYPE_PROMPT           2

#define     ERROR_DEVICE_AUSTONE        1
#define     ERROR_DEVICE_AUSTONE_IN_ONE 2
#define     ERROR_DEVICE_ESR            3
#define     ERROR_DEVICE_PLC            100
#define     ERROR_DEVICE_AXIS           101
#define     ERROR_DEVICE_HMI            10000


#define     ERROR_OBJECT_N2C            1
#define     ERROR_OBJECT_E2C            2
#define     ERROR_OBJECT_COM2           3
#define     ERROR_OBJECT_55ERROR2       4
#define     ERROR_OBJECT_RS485          5
#define     ERROR_OBJECT_TMIOT          11
#define     ERROR_OBJECT_M3ERROR        89
#define     ERROR_OBJECT_AUSTONE        100
#define     ERROR_OBJECT_SIEMENS        101
#define     ERROR_OBJECT_TM             102
#define     ERROR_AMMETER_TM            103
#define     ERROR_ROBOT_RS485           104
#define     ERROR_OBJECT_ESR            105

enum        MONTH {JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC};

#define     DATE_OK             0
#define     TIME_OK             0
#define     DATE_ERROR_YEAR     1
#define     DATE_ERROR_MONTH    2
#define     DATE_ERROR_DAY      3
#define     TIME_ERROR_HOUR     4
#define     TIME_ERROR_MINUTE   5
#define     TIME_ERROR_SECOND   6

#define     ROC_START           1911
#define     C20_START           1900

//typedef     short               BOOL;
typedef     unsigned char       BYTE;
typedef     unsigned short      WORD;

typedef     long                LONG;


//typedef     unsigned      int   DWORD;

typedef     DWORD               FGC;        // Foreground color
typedef     DWORD               BGC;        // Background color
typedef     WORD                tmHWND;       // Handle of window
typedef     unsigned int        UINT;
// typedef     UINT                WPARAM;
//typedef     DWORD               LPARAM;
typedef     DWORD               _TIMEL;
typedef     DWORD               _COUNTL;
typedef     DWORD               _FLAGL;

//typedef        char                INT8;
typedef        short                INT16;


//typedef        long                INT32;


//typedef        long long            INT64;

typedef        unsigned char        UINT8;
typedef        unsigned short        UINT16;

//typedef        unsigned long        UINT32;

//typedef        unsigned long long    UINT64;

typedef        unsigned int        UINT;

typedef	struct tagtmDATE
{
    BYTE	day;
    BYTE	month;
    WORD	year;
    BYTE	dayofweek;
}__attribute__((packed, aligned(2))) tmDATE;

typedef	struct	tagtmTIME
{
    BYTE	hour;
    BYTE	minute;
    BYTE	second;
    BYTE	hsecond;
}__attribute__((packed, aligned(2))) tmTIME;

typedef struct tagOPERATION
{
    DWORD	dwFlag;						// flag						0x1234ABCD
    char    cMachineID[8+1];            // 機台編號                 // 0-7 (unit=BYTE)
    tmDATE  dateMachineOut;             // 機台出廠日期             // 8,9,10,12
    tmDATE  dateMachineSell;            // 機台交易日期             // 8,9,10,12
    BYTE    cState;                     // 運轉狀態                 // 14
    BYTE    cStages;                    // 期數                     // 15
    BYTE    cStageNow;                  // 當前期數                 // 16
    WORD    cDaysTimeoutPeriod;         // 單期停車天數             // 17
    tmDATE  dateTimeout;                // 下期停車日期             // 18,19,20,22
    WORD    cDaysTimeoutAlarmPeriod;    // 警告天數                 // 24
    tmDATE  dateTimeoutAlarm;           // 下次警告日期             // 26,27,28,30
    tmTIME	timeStop;					// 停車時間LEO20050119 Judge time on work
    short   nMinuteTimeoutAlarmInterval;// 警告間隔分鐘             // 32-33
    long    lMinute;                    // 運轉時數                 // 34-37
    long    lMinuteMotor;               // Motor on  minute
    long    lMinuteAuto;                // Automode  minute
    BOOL    bTimeout;                   // 警告旗標                 // 38,39
    WORD	wCRC;
    char    cMachineType[9];            // 機台型號                 // //YANGY2010-1-13
    tmDATE	CurrentData;				//上一次存儲日期
    tmTIME	CurrentTime;				//上一次存儲時間
    WORD	wBatNotExit;				//檢測電池不存在3次則停機
} OPERATION;

#endif
