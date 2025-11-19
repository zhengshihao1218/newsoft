/* Copyright (C), 2004-2009, Techmation. Co., Ltd.*/ 

/*===========================================================================+
|  Class    : tmSQLiteStorage                                                |
|  Task     : tmSQLiteStorage header file                                    |
|----------------------------------------------------------------------------|
|  Compile  : G++(GCC)3.2                                                    |
|  Link     : G++(GCC)3.2                                                    |
|  Call     :                                                                |
|----------------------------------------------------------------------------|
|  Author   : Caozz                                                          |
|  Version  : V1.00                                                          |
|  Creation : 2017.10.17                                                     |
|  Revision :                                                                |
+===========================================================================*/
#ifndef D_TMSQLITEALARM
#define D_TMSQLITEALARM

#include "tmSQLiteStorage.h"

#define     ALARM_DIR           "alarm/"

#define     ALARM_NAME          "Alarm"

class CtmSQLiteAlarm: public CtmSQLiteStorage
{
    public:
        CtmSQLiteAlarm(int nMaxNum);
        ~CtmSQLiteAlarm();
    public:
        int             CreateSelf();
        int             FreeSelf();        
        
        int             GetMaxNum();
        int             GetNum();
        BOOL            Save(tmSQLite_ERROR  TempError);
        tmSQLite_ERROR* GetErrorLog(int nStart, int nCount);
        tmSQLite_ERROR* GetErrorLog(int nRowid);
        tmSQLite_ERROR* GetErrorLog(tmSQLite_ERROR* TempError);//跟据警报的device subIndex errorID查找记录

        BOOL            DeleteRecord();

        int             Find(tmSQLite_ERROR  TempError);

        QString         ParseErrorID(tmSQLite_ERROR* pErrorInfo);
    
    private:
        pthread_mutex_t m_Mutex;
        void            SetFileName();
        void            Init_Alarm();
        void            Init_Mem(tmSQLite_ERROR* pErrorInfo);

    private:
        int             m_nMaxNum;
        char            m_szFileName[128];
        tmSQLite_ERROR  m_CurrentError;
        tmSQLite_ERROR* m_pErrorHead;

    
};

#endif
