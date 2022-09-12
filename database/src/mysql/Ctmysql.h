///////////////////////////////////////////////////////////
//  Ctmysql.h
//  Original author: wakamda
//  class Ctmysql describtion
///////////////////////////////////////////////////////////
#ifndef _CTMYSQL_H
#define _CTMYSQL_H

#include <iostream>
#include "../basic/Basic_db.h"
#include "../common/include/mysql.h"

using namespace std;

class Ctmysql :public Basic_db
{
    public:
    Ctmysql() {};
    ~Ctmysql() {};
/************************************************************************
 *  config
************************************************************************/

    //create instance
    ERR_CODE Init();
    ERR_CODE Finit();

    //connect mysql
    ERR_CODE connectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag);
    
    //Set the database encoding format
    ERR_CODE SwitchDBType(TABLE_CODING_TYPE type);

    //Set additional connection options in mysql
    ERR_CODE SetMysqlOption(MSQL_OPT opt,const void *arg);

    //Set the connect timeout seconds
    ERR_CODE SetConnectTimeout(int sec);

    //Automatic reconnection, not automatic by default
    ERR_CODE SetReconnect(bool isre);

/************************************************************************
 *  operation
************************************************************************/

    //Query SQL(can not parse sql with bin sql)
    bool Query(const char*sql, unsigned long sqllen = 0);
    
    //database
    ERR_CODE createdatabase(std::string &dbname);
    ERR_CODE deletedatabase(std::string &dbname);

    //table
    ERR_CODE createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_CODING_TYPE tablecodingtype);
    ERR_CODE deletetable(std::string &tablename);

    //data insert 
    ERR_CODE Insert(TableDataMap &da, std::string &tablename);

    //data delete with id
    ERR_CODE DeleteDataWithId(std::string &tablename, std::string &idname, std::string &idnum);

    //delete data where fieldname like ...
    ERR_CODE DeleteDataLikeWithFieldname(std::string &tablename, std::string &fieldname, std::string &fielddata);

    //update data
    uint64_t UpdateData(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum);

    //select table
    ERR_CODE SelectFromTable(std::string &tablename);



    //select data where like...
    ERR_CODE SelectDataWithX(std::string &tablename, std::string &fieldname, std::string &fielddata);

    //select data returns all results
	ERR_CODE StoreResult();

    //Start receiving results, Fetch via Fetch
	ERR_CODE UseResult();

    //Frees the space occupied by the result set
    ERR_CODE FreeResult();

    //receive a row data
    ROW FetchRow();

    //Simple interface, return select data results, each call to clean up the last result set  
	ERR_CODE EasySelect(std::string &tablename, ROWS &rows);

	//模糊查询
	ERR_CODE EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, ROWS &rows);
 
     
/***********************************************************************
 * underlying operation
************************************************************************/
private:
    //set the table field type string accroding to the TABLE_FIELD_TYPE
    std::string GetTableFieldTypeString(TABLE_FIELD_TYPE gbkorutf);

    //autogen sql to create table
    std::string GetAutogenCreateSql(LPTABLESTRUCT pfield);

    //auto gen sql to insert data in table
    std::string GetAutogenInsertSql(TableDataMap &da, std::string &tablename);

    //auto gen sql to update data in table
    std::string GetAutogenUpdateSql(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum);
    
    
    MYSQL *mysql;      //connect mysql pointer 
    MYSQL_RES *result; //result pointer
    MYSQL_ROW row;     //result of select data

};


#endif //_CTMYSQL_H
