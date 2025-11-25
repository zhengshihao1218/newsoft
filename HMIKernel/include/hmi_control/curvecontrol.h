#ifndef CURVECONTROL_H
#define CURVECONTROL_H
#include "../common.h"

#define     MAX_CURVE           16
#define     MAX_Y_NUM           8
#define     MAX_POINT_NUM       2000

#define     DISK_RESERVE_SIZE   300*1024*1024       // disk residue size 300MB

#define     MAX_ONE_FILE_SIZE   50*1024*1024        //file size 50MB


#define        CURVE_NONE       0
#define        CURVE_UPDATE     1
#define        CURVE_DONE       2


#define     CURVE_DATA_PATH      "curve/"


typedef    struct tagCURVE_POINT
{
    qint64  llDateTime;
    QList<float> listY;
} tmCURVE_POINT;

typedef    struct tagCURVE_DATA
{
    int nState;
    int nCount;
    QList<tmCURVE_POINT> listPoint;
} tmCURVE_DATA;

class CtmCurveControl
{
public:
    CtmCurveControl();
    static CtmCurveControl* GetInstance();

    int                     AddPoint(int nCurveIndex, tmCURVE_POINT* pPointData, int nCurveNum, BOOL bSaveFlag = FALSE);

    /*
        获取曲线ID为 nCurveIndex 的实时曲线的集合。
    */
    QList<tmCURVE_POINT>    GetCurveData(int nCurveIndex);

    /*
        获取产品名称为 strPath , 起始时间为StartTime, 结束时间为EndTime, 曲线ID为 nCurveIndex 的曲线的集合。
        StarTime,EndTime 为 自 1970-01-01T00:00:00.000以来的毫秒，如果EndTime=0，则为当前时间。
    */
    QList<tmCURVE_POINT>    GetHistoryCurve(int nCurveIndex, QString strPath, qint64 StartTime, qint64 EndTime = 0);

    /*
        获取产品名称为 strPath ,曲线ID为 nCurveIndex 的曲线保存的文件名称的集合。
    */
    QStringList             GetHistoryFileList(int nCurveIndex, QString strPath);//added @20230108
    long long               CheckProCurveStartTime(int nCurveIndex, QString strPath, long long historyTime, bool isMoveToLeft);

    int                     GetCurveState(int nCurveIndex);
    int                     SetCurveState(int nCurveIndex, int nState);

    QString                 SetCurveSavePath(int nCurveIndex, QString strPath);

    int                     SetOneFileSize(int nSize);
    int                     GetOneFileSize();
    int                     SetDiskReserveSize(int nSize);
    int                     GetDiskReserveSize();

    BOOL                    ClearData(int nCurveIndex);
    BOOL                    ClearData(int nCurveIndex, QString strPath);

    void                    SaveHistoryCurve(int nCurveIndex = -1);
private:
    void                    Init();
    int                     SaveToFile(int nCurveIndex, tmCURVE_DATA CurveData);
    QString                 GetCurrentFile(int nCurveIndex, tmCURVE_DATA CurveData);
    quint64                 GetDiskResidueSize();
private:
    static CtmCurveControl* m_pSelf;

   QMutex                   mutex;
   QString                  m_strFileDir;
   QString                  m_strSavePath[MAX_CURVE];

   int                      m_nOneFileSize;
   int                      m_nDiskReserveSize;
   tmCURVE_DATA             m_aryPoints[MAX_CURVE];
   tmCURVE_DATA             m_aryLastPoints[MAX_CURVE];
};

#endif // CURVECONTROL_H
