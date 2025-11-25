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
#ifndef D_TMSQLITEUSER
#define D_TMSQLITEUSER

#include "tmSQLiteStorage.h"

#define     USER_DIR           "user/"

#define     USER_NAME          "User"

class CtmSQLiteUser: public CtmSQLiteStorage
{
    public:
        CtmSQLiteUser(int nMaxNum);
        ~CtmSQLiteUser();
    public:
        int             CreateSelf();
        int             FreeSelf();        
        
        int             GetMaxNum();
        int             GetNum();


        int             AddUser(tmSQLite_User  userInfo);
        BOOL            DeleteUser(WORD wType, tmSQLite_User  userInfo);
        
        tmSQLite_User*  GetUserInfo(int nStart, int nCount);
        tmSQLite_User*  LoginUser(WORD wType, tmSQLite_User  userInfo);
        BOOL            LogoutUser();
        BOOL            ModifyUser(tmSQLite_User  userInfo);
        int             Find(WORD wType, tmSQLite_User  userInfo);
        BOOL            SetCurrentUser(tmSQLite_User  userInfo);
        tmSQLite_User*  GetCurrentUser();

        BOOL            DeleteRecord();
    
    private:
        pthread_mutex_t m_Mutex;
        void            SetFileName();
        void            Init_User();
        void            Init_Mem(tmSQLite_User* pUserInfo);
        QString         Encrypt(QString strPW);
        BOOL            isExistUser(tmSQLite_User  userInfo);
    private:
        int             m_nMaxNum;
        char            m_szFileName[128];
        tmSQLite_User  m_CurrentUser;
        tmSQLite_User* m_pUserInfoHead;

    
};
#endif
