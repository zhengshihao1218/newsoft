/*==========================================================================+
|  Class    : Strings                                                        |
|  Task     : Strings header file                                              |
|---------------------------------------------------------------------------|
|  Compile  : G++ V3.2.2 -                                                  |
|  Link     : G++ V3.2.2 -                                                  |
|  Call     :                                                               |
|---------------------------------------------------------------------------|
|  Author   : netdigger                                                     |
|  Version  : V1.00                                                         |
|  Creation : 2006/1/24                                                       |
|  Revision :                                                                 |
+==========================================================================*/
#ifndef    D_DSTRINGS
#define    D_DSTRINGS

#include "common.h"
/*==========================================================================+
|           Constant                                                        |
+==========================================================================*/

/*==========================================================================+
|           Type definition                                                 |
+==========================================================================*/
typedef struct tagSTRINGSINFO
{
    int             nCount;
    int             nSize;
}STRINGSINFO;

typedef    struct    tagSTRING
{
    int             nIndex;
    char*           pStr;
    tagSTRING       *pLNode;
    tagSTRING       *pRNode;
}STRING;

//    fans add
typedef enum{NULLKEY = 0,HAVEKEY,DELKEY} tmHaveHashKey;

typedef    struct    tagHASHELEMENT
{
    unsigned int    uiIndex;
    unsigned int    uiSizeOfData;
    void*           pKey;
    void*           pData;
    tagHASHELEMENT* pLNode;
    tagHASHELEMENT* pRNode;
}tmHashElement;

typedef struct     tagHASHTABLE
{
    unsigned int    uiCount;
    unsigned int    uiSize;
    tmHashElement*  pElements;
}tmHashTable;

/*==========================================================================+
|           Function and Class prototype                                    |
+==========================================================================*/

/*==========================================================================+
|           Class declaration - CStrings                                    |
+==========================================================================*/
class CStrings
{
/*--------------------------------------------------------------------------+
|           Constructor and destructor                                      |
+--------------------------------------------------------------------------*/
public:
    CStrings();
    ~CStrings();
/*--------------------------------------------------------------------------+
|           Operations                                                      |
+--------------------------------------------------------------------------*/
public:
    int         Create(STRINGSINFO *pInfo);
    int         AddString(const char *psz);

    int         GetIndex(char *psz);
    char*       GetString(int nIndex);

/*--------------------------------------------------------------------------+
|           Attributes                                                      |
+--------------------------------------------------------------------------*/
private:
    int         m_nCount;
    int         m_nListCount;
    int         m_nStrSize;

    char        *m_pStrings;
    char        **m_pStringIndex;
    STRING      *m_pStringList;
    STRINGSINFO m_Info;

    void        FreeList();
    void        FreeNode(STRING* pString);
    int         GetNearPrime(int nCount);
    int         GetHash(char *psz);
    int         AddList(STRING *pStrInfo);
};


/*==========================================================================+
|           Class declaration - CtmHashTable                                 |
+==========================================================================*/
class CtmHashTable
{
    /*--------------------------------------------------------------------------+
    |           Constructor and destructor                                      |
    +--------------------------------------------------------------------------*/
    public:
        CtmHashTable(unsigned int    uiNum = 6151);
        virtual    ~CtmHashTable();
    /*--------------------------------------------------------------------------+
    |           Operations                                                      |
    +--------------------------------------------------------------------------*/
    public:
        virtual     BOOL            AddElement(tmHashElement* pElement);
        virtual     BOOL            DelElement(void* pKey);
        virtual     BOOL            FindElement(void* pKey, tmHashElement* pOutElement);
        virtual     const tmHashTable* GetHashContent() {return &m_HashTable;}
        virtual     void            ClearElement();
    protected:
        virtual     void            InitHash();
        virtual     void            FreeHash();
        virtual     void            FreeNode(tmHashElement* pNode);
        virtual     int             Hash(void* pKey);
        virtual     int             EqualKey(void* pKey, void* pHashKey);
        virtual     tmHashElement*  FindElementEmptyPos(void* pKey);
        unsigned int                GetPrime(unsigned int uiNum);
    /*--------------------------------------------------------------------------+
    |           Attributes                                                      |
    +--------------------------------------------------------------------------*/
    protected:
        unsigned int        m_iHashSeed;
    private:
        tmHashTable         m_HashTable;

};



#endif

