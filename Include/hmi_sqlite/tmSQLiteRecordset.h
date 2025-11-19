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
#ifndef D_TMSQLITERECORDSET
#define D_TMSQLITERECORDSET

#include "tmSQLiteStorage.h"

#define     RECORDSET_DIR       "recordset/"

#define     RECORDSET_NAME      "Recordset"

class CtmSQLiteRecordset: public CtmSQLiteStorage
{
    public:
        CtmSQLiteRecordset(int nMaxNum);
        ~CtmSQLiteRecordset();
    public:
        int             CreateSelf();
        int             FreeSelf();        
        
        int             GetMaxNum();
        int             GetNum();
        BOOL            Save(tmModifyRecordSet  TempRecord);
        BOOL            GetModifyRecordS_FT(int nIndex, char** pOutAction, void* pOutData);


        BOOL            DeleteRecord();
        int             Find(tmModifyRecordSet  TempRecord);
        tmModifyRecordSet* GetRecordLog(int nRowid);
        
    private:
        pthread_mutex_t m_Mutex;
        void            SetFileName();
        void            Init_Recordset();
    private:
        int             m_nMaxNum;
        char            m_szFileName[128];

        tmModifyRecordSet m_CurrentRecord;
        char*           m_pszOutAction;
    
};

#endif
