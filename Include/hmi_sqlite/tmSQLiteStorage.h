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
#ifndef D_TMSQLITESTORAGE
#define D_TMSQLITESTORAGE

#include "../common.h"
#include "../global.h"
#include "../database/database.h"
#include "../device/device.h"

#define		DEFINE_STORAGE_NUM  8

#define     SORT_TYPE_DESC      0
#define     SORT_TYPE_ASC       1

#define     SORT_BY_DATE        0
#define     SORT_BY_NAME        1

#define     USER_LOGIN_ID       0       //only ID
#define     USER_LOGIN_ID_PW    1       //ID&PW
#define     USER_LOGIN_PW       2       //only PW
#define     USER_LOGIN_RFID     3       //RFID
#define     USER_LOGIN_FP       4       //fingerprint
#define     USER_LOGIN_QRCODE   5       //QR code

#define     USER_ERROR_NULL     0
#define     USER_ERROR_FULL     1
#define     USER_ERROR_EXIST    2
#define     USER_ERROR_OTHER    3


typedef struct tagtmSQLite_ERROR
{
    QString     strUserID;
    WORD        wGrade;
    WORD        wDevice; 
    WORD        wSubIndex;
    DWORD       dwErrorID;
    DWORD       dwShotCount;
    QString     strDateTimeStart;
    QString     strDateTimeFixed;
}
tmSQLite_ERROR;

typedef struct tagtmSQLite_User
{
    QString     strUserID;
    QString     strPassword;
    QString     strUserName;
    QString     strUserRFID;
    QString     strUserFP;
    QString     strUserQRCode;
    WORD        wPrivilege;
    WORD        wSource;
    QString     strDateTimeCreate;
}
tmSQLite_User;

typedef struct tagDB_MOLDHDR
{
    QString    strID;
    QString	   strDateSave;
    QString    strMaterial;
    QString    strColor;
    WORD       cUnitCount;
    WORD	   Media;
}
DB_MOLDHDR;

typedef	struct tagtmModifyRecordSet
{
    QString     strUserID;
    QString     strDateTime;
    int         DBIndex;
    long long   OldValue;
    long long   NewValue;
}tmModifyRecordSet;

/*===========================================================================+
|           Class declaration - CtmSQLiteStorage                             |
+===========================================================================*/
class   CtmSQLiteStorage
{
    public:
        enum StorageType
        {
            Moldset         = 0x001,
            Alarm           = 0x002,
            Recordset       = 0x003,
            User            = 0x004
        };

        CtmSQLiteStorage();  
        virtual ~CtmSQLiteStorage();
    public:
        static CtmSQLiteStorage*GetStroage(StorageType storageType);
    public:
        virtual int             GetMaxNum()                                                     {return 0;}
        virtual int             GetNum()                                                        {return 0;}
        virtual BOOL            DeleteRecord()                                                  {return FALSE;}

    public:
        virtual char*           GetCurrentMold()                                                {return NULL;}
        virtual BOOL            Save(DB_MOLDHDR MoldSetHead)                                    {return FALSE;}
        virtual BOOL            Read(DB_MOLDHDR MoldSetHead)                                    {return FALSE;}
        virtual BOOL            Delete(DB_MOLDHDR MoldSetHead)                                  {return FALSE;}
        virtual int             Find(DB_MOLDHDR MoldSetHead)                                    {return 0;}

        virtual DB_MOLDHDR*     GetMoldSetHead(int nStart, int Num, WORD wSortType, WORD wSortOrder){return NULL;}

        virtual BOOL            isExistMold(DB_MOLDHDR MoldSetHead)                             {return FALSE;}

        virtual int             SendControlMoldSet(char* pszHostType)        {return 0;}

    public:
        virtual BOOL            Save(tmModifyRecordSet  TempRecord)                             {return FALSE;}
        virtual BOOL            GetModifyRecordS_FT(int nIndex, char** pOutAction, void* pOutData){return FALSE;}

        virtual int             Find(tmModifyRecordSet TempRecord)                              {return 0;}


    public:

        virtual BOOL            Save(tmSQLite_ERROR  TempError)                                 {return FALSE;}
        virtual tmSQLite_ERROR* GetErrorLog(int nStart, int nCount)                             {return NULL;}
        virtual tmSQLite_ERROR* GetErrorLog(int nRowid)                                         {return NULL;}//根据行号查找警报
        virtual tmSQLite_ERROR* GetErrorLog(tmSQLite_ERROR* TempError)                          {return NULL;}//根据警报的device subIndex errorID查找记录

        virtual int             Find(tmSQLite_ERROR TempError)                                  {return 0;}
        virtual QString         ParseErrorID(tmSQLite_ERROR* pErrorInfo)                        {}

//    public:
//        virtual BOOL            Save(tmDB_MONI2  TempMoni)                                      {return FALSE;}
//        virtual tmDB_MONI2*     GetMoniLog(int nRowid)                                          {return NULL;}

//        virtual int             Find(tmDB_MONI2  TempMoni)                                      {return 0;}

    public:
        virtual int             AddUser(tmSQLite_User  userInfo)                                {return 0;}
        virtual BOOL            DeleteUser(WORD wType, tmSQLite_User  userInfo)                 {return FALSE;}
        
        virtual tmSQLite_User*  GetUserInfo(int nStart, int nCount)                             {return NULL;}
        virtual tmSQLite_User*  LoginUser(WORD wType, tmSQLite_User  userInfo)                  {return NULL;}
        virtual BOOL            LogoutUser()                                                    {return FALSE;}
        virtual BOOL            ModifyUser(tmSQLite_User  userInfo)                             {return FALSE;}
        virtual int             Find(WORD wType, tmSQLite_User  userInfo)                       {return 0;}
        virtual BOOL            SetCurrentUser(tmSQLite_User  userInfo)                         {return FALSE;}
        virtual tmSQLite_User*  GetCurrentUser()                                                {return NULL;}
    public:
        BOOL                    SaveSQLiteDBFromDB(char* pszFileName, char** pszDBIDList, int nNum);
        BOOL                    SaveSQLiteDBFromDB(char* pszFileName, WORD  wBlockID);
        BOOL                    ReadDBFromSQLiteDB(char* pszFileName);
        BOOL                    DeleteSQLiteDB(char* pszFileName);
        
        char*                   SetDataPath(char* pszPath);
        char*                   GetDataPath();
    protected:
        void                    AddStroage(StorageType storageType, CtmSQLiteStorage* p);
        void                    DelStroage(StorageType storageType);

        int                     OpenSQLiteDB(char* pszFileName);
        int                     CloseSQLiteDB();

        void                    Init();
    protected:

        QSqlDatabase            m_db;
        char                    m_pszDataPath[256];
        BOOL                    m_bDBIsOpen;

        static CtmSQLiteStorage* m_pStorage[DEFINE_STORAGE_NUM];

};


#endif
