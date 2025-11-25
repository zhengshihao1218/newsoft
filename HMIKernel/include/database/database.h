/*==========================================================================+
|  Class    : Database 			                                            |
|  Task     : Database header file                          				|
|---------------------------------------------------------------------------|
|  Compile  : G++ V3.2.2 -                                                  |
|  Link     : G++ V3.2.2 -                                                  |
|  Call     :                                                               |
|---------------------------------------------------------------------------|
|  Author   : netdigger                                                     |
|  Version  : V1.00                                                         |
|  Creation : 2005/5/19                                                    	|
|  Revision : 			                                                    |
+==========================================================================*/
#ifndef		D_DDATABASE
#define		D_DDATABASE

#include	"../common.h"
#include	"../strings.h"
#include    "cblock.h"

#include    "../device/device.h"

/*==========================================================================+
|           Constant                                                        |
+==========================================================================*/
#define		DB_SUCCESS			0x0000
#define		DB_ERR_DBNAME		0x0001
#define		DB_ERR_PROFILE		0x0002
#define		DB_ERR_DB			0x0004
#define		DB_ERR_DBDEFFILE	0x0008
#define		DB_ERR_DATAATTR		0x0010
#define		DB_ERR_DBDEF		0x0040

#define		DB_ERR_FATAL		(DB_ERR_DATAATTR | DB_ERR_DB)

#define		DB_ERR_OUTRANGE		0x0001
#define		DB_ERR_NOUSED		0x0002

#define		DB_ERR_DATA			0x0008
#define		DB_ERR_TYPE			0x0010
#define		DB_ERR_ID			0x0020

#define		DATA_PATH_ELECTRIC		1
#define		DATA_PATH_HYDRAULIC		2
#define		DATA_PATH_I32			4
#define		DATA_PATH_KEB			8
#define		DATA_PATH_HMI			16
#define		DATA_PATH_DSP28			32
#define		DATA_PATH_AUSTONE		512
#define		DATA_PATH_PLC           1024
#define		DATA_PATH_HYDRAULIC2	2048


/*==========================================================================+
|           Type definition                                                 |
+==========================================================================*/


typedef	struct tagDATATYPE
{
    unsigned short	wType;
    unsigned short	wLength;
}	DATATYPE;

typedef struct tagDB_DATAATTRIBUTE
{
    DWORD	dwOffset;
    DATATYPE	DataType;
    DWORD	dwDataPath;
    DWORD	dwMaxIndex;
    DWORD	dwMinIndex;
    WORD		wDataLabel;
    WORD		wPrecision;
    DWORD	dwPrivilege;
    DWORD	dwPowerSupply;
    DWORD	dwUnit;
    WORD		wDisplayPrecision;
}
__attribute__((packed, aligned(2)))	DB_DATAATTRIBUTE;

typedef union	tagDBDATA
{
    char 			acData[8];
    unsigned char 	ucData;
    unsigned short	wData;
    unsigned long	dwData;
    signed char 	cData;
    signed short	nData;
    signed long		lData;
    float 			fData;
    double 			dData;
    char			*pcData;
} DBDATA;

typedef	struct	tagDBVALUE
{
    DWORD			dwIndex;
    DATATYPE                    DataType;
    DWORD			dwDataPath;
    DWORD			dwPowerSupply;
    DWORD			dwMaxIndex;
    DWORD			dwMinIndex;
    WORD			wDataLabel;
    WORD			wPrecision;
    WORD			wDisplayPrecision;
    DWORD			dwPrivilege;
    DWORD			dwUnit;
    long			lID;
    unsigned int 	dwState;
    union
    {
        char 			acData[8];
        unsigned char 	ucData;
        unsigned short	wData;
        unsigned long	dwData;
        signed char 	cData;
        signed short	nData;
        signed long		lData;
        float 			fData;
        double 			dData;
        char			*pcData;
    };
}	DBVALUE;

typedef struct tagDBVIEWVALUE
{
    long long	lValue;
    long long	lMaxValue;
    long long	lMinValue;
    WORD		wPrecision;
    WORD		wDisplayPrecision;
    DWORD		dwPrivilege;
}	DBVIEWVALUE;


typedef	struct tagINDEX2ID
{
    int		nIndex;
    long	lDataID;
}	INDEX2ID;

typedef struct tagDB_PATHMAP
{
    int nAID;
    QString strName;
}
DB_PATHMAP;

typedef struct tagDB_LIMITMAP
{
    int nAID;
    QString strName;
}
DB_LIMITMAP;

typedef struct tagDB_MEMORYMAP
{
    int nAID;
    int nSize;
    QString strName;
}
DB_MEMORYMAP;

typedef struct tagDB_TYPEMAP
{
    char szPath[256];
    char szLocalMeoryType[256];
    char szDataType[256];
}
DB_TYPEMAP;

typedef struct tagDB_BLOCKMAP
{
    int nIndex;
    int nBlockIndex;
    QString strName;
}
DB_BLOCKMAP;


typedef struct tagDB_BLOCKDATA
{
    int  nDataIndex;
    int  nInnerIndex;
    int  nDataKind;
}
DB_BLOCKDATA;

typedef struct tagDB_IDTYPE
{
    long 			lDataID;
    DATATYPE 		DataType;
}
DB_IDTYPE;


/*===========================================================================+
|           Function and Class prototype                                     |
+===========================================================================*/

/*===========================================================================+
|           Class declaration - Wnd                                          |
+===========================================================================*/
class CDatabase
{
public:
    CDatabase(QString strDataPath);
    ~CDatabase();

private:
    QSqlDatabase        m_db;
    WORD		m_wState;
    int			m_nIDCount;

    char*		m_pcDB;
    char*		m_pcDefDB;
    QFile               m_DBFile;

    CStrings*		m_pIDList;
    DB_DATAATTRIBUTE*	m_pDataAttr;

    const char*         m_pszDBName;
    DWORD		m_dwLength;

    char*		m_BlockBuff;
    pthread_mutex_t	mutex;

    int			m_nMaxIndex;
    INDEX2ID*		m_pIndexToID;
    long		m_lMaxDataID;


    DB_TYPEMAP*		m_pDBTypeMap;
    DB_BLOCKMAP*	m_pDBBlockMap;
    DB_BLOCKDATA*	m_pDBBlockData;

    int 		m_nDBTypeMapCount;
    int 		m_nDBBlockMapCount;
    int 		m_nDBBlockCount;
    int			m_nDBState;
public:
    int			Create(QString strDataPath);
    int			GetIndex(char *psz);
    int			GetDataID(char *psz);
    char*		GetString(int nIndex);
    int			Save(int nLength=-1, int nOffset=-1, int nIndex=-1);

    char*		Reads(int nIndex);
    DBVALUE		Read(int nIndex);
    DBVALUE		Read(char* pID);
    DBVALUE		ReadDefault(int nIndex);
    DBVALUE		ReadDefault(char* pID);

    char*		Writes(char *psz, int nIndex, int nLength, BOOL bSave = TRUE);
    DBVALUE*		Write(DBVALUE *pData, BOOL bSave = TRUE);
    DBVALUE		Write(int nIndex, void *pData, BOOL bSave = TRUE);
    DBVALUE		Write(char *pID, void *pData, BOOL bSave = TRUE);
    DBVALUE		WriteDefault(int nIndex, void *pData, BOOL bSave = TRUE);
    DBVALUE		WriteDefault(char *pID, void *pData, BOOL bSave = TRUE);

    int			DataIDToIndex(long lDataID);
    long		IndexToDataID(int nIndex);
    int			GetIDCount() { return m_nIDCount;}
    DWORD		GetDBSize()	{ return m_dwLength; }
    void		Reset();
private:
    int 		CheckDBFile(const char* pszFileName);
    int			LoadDB(QString strDataPath);
    int			OpenSQLiteDB(QString strDataPath);
    int			CloseSQLiteDB();
    int     		LoadSQLiteDB();

    int 		LoadSQLiteDBPath();
    int 		LoadSQLiteDBLimitMap();
    int 		LoadSQLiteMemoryMap();
    int   		LoadSQLiteTypeMap();
    int   		LoadSQLiteBlockMap();
    int 		LoadSQLiteBlock();

    char*		FindDBType(const char* pszPath, const char* pszLocalMemoryType);


};

extern          CDatabase*  g_pDatabase;

/*
    获取索引为 wIndex的资料的数据。
 */
DBVIEWVALUE		GetDBValue(WORD	wIndex);

/*
    获取名字为 pcID 的资料的数据，如果没找到 *pbFind = true, 周到pbFind = false。
 */
DBVIEWVALUE		GetDBValue(char* pcID, BOOL* pbFind = NULL);

/*
    获取ID为 pcID 的资料的数据，如果没找到 *pbFind = true, 周到pbFind = false。
 */
DBVIEWVALUE		GetIDValue(DWORD dwDataID);

/*
    获取索引为 wIndex的资料的默认值。
 */
DBVIEWVALUE		GetDBDefaultValue(WORD wIndex);

/*
    获取名字为 pcID 的资料的默认值。
 */
DBVIEWVALUE		GetDBDefaultValue(char* pcID);

/*
    获取名字为 pcID 的资料的字符串的值，nLength 为pcID的最大长度，pszStr保存的指针。
    若成功，返回值为0，否则不为0
 */
WORD			GetDBString(char* pcID, char* pszStr, int nLength);

/*
    设置名字为 pcID 的资料的字符串的值，nLength 为pcID的最大长度，pszStr保存的指针。
    若成功，返回值为0，否则不为0
 */
WORD			SetDBString(char* pcID, char* pszStr, int nLength);

/*
    设置名字为 pcID 的资料的字符串的值，lValue 为资料值和该资料精度的乘积，bSend为true,发送至PLC, 否则不发送。
    若成功，返回值为0，否则不为0
 */
WORD			SetDBValue(char* pcID, long long lValue, BOOL bSend=TRUE);

/*
    设置索引为 wIndex 的资料的字符串的值，lValue 为资料值和该资料精度的乘积，bSend为true,发送至PLC, 否则不发送。
    若成功，返回值为0，否则不为0
 */
WORD			SetDBValue(WORD	wIndex, long long lValue, BOOL bSend=TRUE);

/*
    将名字为 pcID 的资料的值为lValue的改动保存至数据库。
    若成功，返回值为0，否则不为0
 */
WORD			SetViewDBValue(char* pcID, long long lValue);

/*
    设置资料ID为 dwDataID 的资料的字符串的值，lValue 为资料值和该资料精度的乘积。
    若成功，返回值为0，否则不为0
 */
WORD			SetIDValue(DWORD dwDataID, long long lValue);



#endif
