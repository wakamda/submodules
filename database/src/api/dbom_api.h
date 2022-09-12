///////////////////////////////////////////////////////////
//  DB_sdk_api.h
//  Original author: wakamda
//  Description file of the DB SDK API
///////////////////////////////////////////////////////////
#ifndef _DB_SDK_API_H
#define _DB_SDK_API_H

#include "../common/Datatype.h"
#include "../mysql/Ctmysql.h"
#include "../log/Log.h"

#define ERROR_NO_ERROR                 (0)
#define ERROR_UNKOWN_ERROR             (-1)
#define ERROR_API_PARAM_INVALID        (-2)
#define ERROR_INTERNEL_PARAM_INVALID   (-3)
#define ERROR_CREATE_CONNECTION_ERR    (-4)

static void* handle = NULL;

typedef enum{
    LOG_VERBOSE    = 0x00, /*!< VERBOSE */
    LOG_DEBUG      = 0x01, /*!< DEBUG  */
    LOG_INFO       = 0x03, /*!< INFO  */ 
    LOG_WARN       = 0x04, /*!< WARN  */
    LOG_ERROR      = 0x05, /*!< ERROR  */
    LOG_FATAL      = 0x06, /*!< FATAL  */
}LogLevel_t;

/************************************************************************
 *  config
************************************************************************/

int SetLogLevel(int level);

int GetLogLevel(void);

/**
 * @brief 创建句柄
 * 
 * @return void * 
 */
bool sdk_Init();

/**
 * @brief 销毁句柄
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_Finit();

/**
 * @brief 连接数据库
 * 
 * @param handle 
 * @param host 
 * @param user 
 * @param pwd 
 * @param db_name 
 * @param port 
 * @param flag 
 * @return ERR_CODE 
 */
ERR_CODE sdk_connectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag = 0);

/**
 * @brief Set the database encoding format
 * 
 * @param handle 
 * @param type 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SwitchDBType(TABLE_CODING_TYPE type = UTF8);

/**
 * @brief Set additional connection options in mysql
 * 
 * @param handle 
 * @param opt 
 * @param arg 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetMysqlOption(MSQL_OPT opt,const void *arg);

/**
 * @brief Set the connect timeout seconds
 * 
 * @param handle 
 * @param sec 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetConnectTimeout(int sec);

/**
 * @brief Automatic reconnection, not automatic by default
 * 
 * @param handle 
 * @param isre 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SetReconnect(bool isre);

/**
 * @brief Get host name
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Gethost();

/**
 * @brief set host name
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Sethost(char* newVal);

/**
 * @brief get username
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Getuser();

/**
 * @brief set username
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setuser(char* newVal);

/**
 * @brief get password
 * 
 * @param handle 
 * @return char* 
 */
char* sdk_Getpwd();

/**
 * @brief set password
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setpwd(char* newVal);

/***/
char* sdk_Getdbname();

/**
 * @brief set database name
 * 
 * @param handle 
 * @param newVal 
 * @return char* 
 */
char* sdk_Setdbname(char* newVal);

/**
 * @brief 
 * 
 * @param handle 
 * @return unsigned short 
 */
unsigned short sdk_Getport();

/**
 * @brief set connection port
 * 
 * @param handle 
 * @param newVal 
 * @return unsigned short 
 */
unsigned short sdk_Setport(unsigned short newVal);

/**
 * @brief 
 * 
 * @param handle 
 * @return unsigned long 
 */
unsigned long sdk_Getflag();

/**
 * @brief set connection flag
 * 
 * @param handle 
 * @param newVal 
 * @return unsigned long 
 */
unsigned long sdk_Setflag(unsigned long newVal);

/************************************************************************
 *  operation
************************************************************************/

/**
 * @brief Query SQL(can not parse sql with bin sql)
 * 
 * @param handle 
 * @param sql 
 * @param sqllen 
 * @return true 
 * @return false 
 */
bool sdk_Query(const char*sql, unsigned long sqllen = 0);

/**
 * @brief create database
 * 
 * @param handle 
 * @param dbname 
 * @return ERR_CODE 
 */
ERR_CODE sdk_createdatabase(std::string dbname);

/**
 * @brief delete database
 * 
 * @param handlestd 
 * @param dbname 
 * @return ERR_CODE 
 */
ERR_CODE sdk_deletedatabase(std::string dbname);

/**
 * @brief create table
 * 
 * @param handle 
 * @param vector 
 * @param tablename 
 * @param tablecodingtype 
 * @return ERR_CODE 
 */
ERR_CODE sdk_createtable(TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype = UTF8);

/**
 * @brief delete table
 * 
 * @param handle 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_deletetable(std::string tablename);

/**
 * @brief data insert 
 * 
 * @param handle 
 * @param da 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_Insert(TableDataMap &da, std::string tablename);

/**
 * @brief data delete with id
 * 
 * @param handle 
 * @param tablename 
 * @param idname 
 * @param idnum 
 * @return RR_CODE 
 */
ERR_CODE sdk_DeleteDataWithId(std::string tablename, std::string idname, std::string idnum);

/**
 * @brief delete data where fieldname like ...
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @return ERR_CODE 
 */
ERR_CODE sdk_DeleteDataLikeWithFieldname(std::string tablename, std::string fieldname, std::string fielddata);

/**
 * @brief update data
 * 
 * @param handle 
 * @param da 
 * @param tablename 
 * @param where 
 * @param idnum 
 * @return UINT64 
 */
uint64_t sdk_UpdateData(TableDataMap &da, std::string tablename, std::string where, std::string idnum);

/**
 * @brief select table
 * 
 * @param handle 
 * @param tablename 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SelectFromTable(std::string tablename);

/**
 * @brief select data where like...
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @return ERR_CODE 
 */
ERR_CODE sdk_SelectDataWithX(std::string tablename, std::string fieldname, std::string fielddata);

/**
 * @brief select data returns all results
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_StoreResult();

/**
 * @brief Start receiving results, Fetch via Fetch
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_UseResult();

/**
 * @brief Frees the space occupied by the result set
 * 
 * @param handle 
 * @return ERR_CODE 
 */
ERR_CODE sdk_FreeResult();

/**
 * @brief receive a row data
 * 
 * @param handle 
 * @return ROW 
 */
ROW sdk_FetchRow( ROW &row);

/**
 * @brief Simple interface, return select data results, each call to clean up the last result set
 * 
 * @param handle 
 * @param tablename 
 * @param rows 
 * @return ERR_CODE 
 */
ERR_CODE sdk_EasySelect(std::string tablename, ROWS &rows);

/**
 * @brief Simple interface, fuzzy search
 * 
 * @param handle 
 * @param tablename 
 * @param fieldname 
 * @param fielddata 
 * @param rows 
 * @return ERR_CODE 
 */
ERR_CODE sdk_EasyLike(std::string tablename, std::string fieldname,std::string fielddata, ROWS &rows);



#endif //_CTMYSQL_API_H
