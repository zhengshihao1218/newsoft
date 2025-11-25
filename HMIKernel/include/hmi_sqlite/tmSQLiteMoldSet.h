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
#ifndef D_TMSQLITEMOLDSET
#define D_TMSQLITEMOLDSET

#include "tmSQLiteStorage.h"

#define     MOLDSET_DIR         "moldset/"

#define     MOLDSETLIST_NAME    "MoldList"
#define     DEFAULT_MOLDNAME    "IMCS"


#define     CURRENT_MOLD_NAME       "MHDR_MODULE_NULL_NULL_MODULENAME"
#define     CURRENT_MOLD_MATERIAL   "MHDR_MODULE_NULL_NULL_MODULEMATERIAL"
#define     CURRENT_MOLD_COLOR      "MHDR_MODULE_NULL_NULL_MODULECOLOR"
#define     CURRENT_MOLD_DAY        "DATE_MODULE_NULL_NULL_MODULEDAY"
#define     CURRENT_MOLD_MONTH      "DATE_MODULE_NULL_NULL_MODULEMONTH"
#define     CURRENT_MOLD_YEAR       "DATE_MODULE_NULL_NULL_MODULEYEAR"
#define     CURRENT_MOLD_WEEK       "DATE_MODULE_NULL_NULL_MODULEWEEK"
#define     CURRENT_MOLD_RESERVED   "DATE_MODULE_NULL_NULL_MODULERESERVED"
#define     CURRENT_MOLD_UNIT       "MHDR_MODULE_NULL_NULL_MODULEUNIT"
#define     CURRENT_MOLD_MEDIA      "MHDR_MODULE_NULL_NULL_MODULEBYMEDIA"


class CtmSQLiteMoldSet: public CtmSQLiteStorage
{
    public:
        CtmSQLiteMoldSet(int nMaxNum, QString strMoldIDList);
        ~CtmSQLiteMoldSet();

    public:
        int             CreateSelf();
        int             FreeSelf();
        
        int             GetMaxNum();
        char*           GetCurrentMold();
        int             GetNum();

        BOOL            Save(DB_MOLDHDR MoldSetHead);
        BOOL            Read(DB_MOLDHDR MoldSetHead);
        BOOL            Delete(DB_MOLDHDR MoldSetHead);

        DB_MOLDHDR*     GetMoldSetHead(int nStart, int Num, WORD wSortType, WORD wSortOrder);

        BOOL            isExistMold(DB_MOLDHDR MoldSetHead);

        int             SendControlMoldSet(char* pszHostType);
        
    private:
        void            Init_Mold();
        void            Init_Mem(DB_MOLDHDR* pMoldHead);

        void            Init();
        void            Init_MoldIDList();
        BOOL            OpenSQLiteMoldListDB();
        void            CreateDefaultMold();
        BOOL            SaveToMoldList(DB_MOLDHDR MoldSetHead);
    private:
        
        DB_MOLDHDR*     m_pHeads;
        int             m_nMaxMoldSet;    
        char            m_szCurrentMoldName[40];

        int             m_nMoldIDCount;
        char**          m_pszMoldIDList;

        static char*    m_pszSortType[];
        static char*    m_pszSortOrderBy[];

        QMap<QString,QStringList>     m_strMoldIDList;
};


#endif
