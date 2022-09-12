///////////////////////////////////////////////////////////
//  Datatype.h
//  Original author: wakamda
//  Basic data type of the Ctmysql SDK
///////////////////////////////////////////////////////////
#ifndef _DATATYPE_H
#define _DATATYPE_H

#include "MysqlType.h"
#include <string>
#include <vector>
#include <map>

/*********************************ERR_CODE*****************************/
typedef enum{
    ERR_SUCCESS = 0,
    ERR_FAILED,
    ERR_INVALID_ARG,
    ERR_INVALID_DATA
}ERR_CODE;

static const char* str_err_code[30] ={
    "ERR_SUCCESS",
    "ERR_FAILED",
    "ERR_INVALID_ARG",
    "ERR_INVALID_DATA"
};
/*********************************table********************************/
//table type
typedef enum{
    UTF8 = 0,
    GBK,
    NOTYPE
}TABLE_CODING_TYPE;

//table field type
enum TABLE_FIELD_TYPE {
	DBTYPE_INT = 0,
	DBTYPE_VARCHAR,
	DBTYPE_DATETIME,
	DBTYPE_BLOB,
	DBTYPE_BINARY,
	DBTYPE_LONGBLOB,
	DBTYPE_MEDIUMBLOB,
	DBTYPE_TINYBLOB,//255
	DBTYPE_VARBINARY,
	DBTYPE_DATA,
	DBTYPE_TIME,
	DBTYPE_TIMESTAMP,
	DBTYPE_YEAR,
	DBTYPE_GEOMETRY,
	DBTYPE_GEOMETRYCOLLECTION,
	DBTYPE_LINESTRING,
	DBTYPE_MULTILINESTRING,
	DBTYPE_MULTIPOINT,
	DBTYPE_POINT,
	DBTYPE_POLYGON,
	DBTYPE_BIGINT,
	DBTYPE_DECIMAL,
	DBTYPE_DOUBLE,
	DBTYPE_FLOAT,
	DBTYPE_MEDIUMINT,
	DBTYPE_REAL,
	DBTYPE_SMALLINT,
	DBTYPE_TINYINT,
	DBTYPE_CHAR,
	DBTYPE_JSON,
	DBTYPE_NCHAR,
	DBTYPE_NVARCHAR,
	DBTYPE_LONGTEXT,
	DBTYPE_MEDIUMTEXT,
	DBTYPE_TEXT,
	DBTYPE_TINYTEXT,
	DBTYPE_BIT,
	DBTYPE_BOOLEAN,
	DBTYPE_ENUM,
	DBTYPE_SET,
	DBTYPE_ID
};

//TABLE_FIELD_TYPE string
static const char* str_table_field_type[41] = {
    "INT",
    "VARCHAR",
    "DATETIME",
    "BLOB",//65K
    "BINARY",
    "LONGBLOB",//4G
    "MEDIUMBLOB",//16MB
    "TINYBLOB",//255
    "VARBINARY",
    "DATA",
    "TIME",
    "TIMESTAMP",
    "YEAR",
    "GEOMETRY",
    "GEOMETRYCOLLECTION",
    "LINESTRING",
    "MULTILINESTRING",
    "MULTIPOINT",
    "POINT",
    "POLYGON",
    "BIGINT",
    "DECIMAL",
    "DOUBLE",
    "FLOAT",
    "MEDIUMINT",
    "REAL",
    "SMALLINT",
    "TINYINT",
    "CHAR",
    "JSON",
    "NCHAR",
    "NVARCHAR",
    "LONGTEXT",
    "MEDIUMTEXT",
    "TEXT",
    "TINYTEXT",
    "BIT",
    "BOOLEAN",
    "ENUM",
    "SET",
    "INT AUTO_INCREMENT"//自增ID
};

//table construct
typedef struct{
    std::string        field_name;
    TABLE_FIELD_TYPE   field_type;
    TABLE_CODING_TYPE  table_coding_type;
    int                field_len = 0;
}TABLESTRUCT, *LPTABLESTRUCT;

//table constrcuction used for create table
typedef std::vector<TABLESTRUCT>   TABLEVECTOR;

/*********************************data********************************/

//table data type
enum TABLE_DATA_TYPE {
	TABLE_DATA_TYPE_DECIMAL,
	TABLE_DATA_TYPE_TINY,
	TABLE_DATA_TYPE_SHORT,
	TABLE_DATA_TYPE_LONG,
	TABLE_DATA_TYPE_FLOAT,
	TABLE_DATA_TYPE_DOUBLE,
	TABLE_DATA_TYPE_NULL,
	TABLE_DATA_TYPE_TIMESTAMP,
	TABLE_DATA_TYPE_LONGLONG,
	TABLE_DATA_TYPE_INT24,
	TABLE_DATA_TYPE_DATE,
	TABLE_DATA_TYPE_TIME,
	TABLE_DATA_TYPE_DATETIME,
	TABLE_DATA_TYPE_YEAR,
	TABLE_DATA_TYPE_NEWDATE, /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_VARCHAR,
	TABLE_DATA_TYPE_BIT,
	TABLE_DATA_TYPE_TIMESTAMP2,
	TABLE_DATA_TYPE_DATETIME2, /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_TIME2,     /**< Internal to MySQL. Not used in protocol */
	TABLE_DATA_TYPE_JSON = 245,
	TABLE_DATA_TYPE_NEWDECIMAL = 246,
	TABLE_DATA_TYPE_ENUM = 247,
	TABLE_DATA_TYPE_SET = 248,
	TABLE_DATA_TYPE_TINY_BLOB = 249,
	TABLE_DATA_TYPE_MEDIUM_BLOB = 250,
	TABLE_DATA_TYPE_LONG_BLOB = 251,
	TABLE_DATA_TYPE_BLOB = 252,
	TABLE_DATA_TYPE_VAR_STRING = 253,
	TABLE_DATA_TYPE_STRING = 254,
	TABLE_DATA_TYPE_GEOMETRY = 255
};

//data struct type
struct Table_Data
{  
	Table_Data(const char* data = 0)
	{
		this->type = TABLE_DATA_TYPE_STRING;
		if (!data)return;
		this->data = data;
		this->size = (unsigned int)strlen(data);
	}
	Table_Data(const uint32_t *d)
	{
		this->type = TABLE_DATA_TYPE_LONG;
		this->data = (const char*)d;
		this->size = sizeof(uint32_t);
	}
	const char * data = 0;
	unsigned int size = 0;
	TABLE_DATA_TYPE type;
};

//插入和更新数据的数据结构,string字段名称,Table_Data字段数据
typedef std::map <std::string, Table_Data>		TableDataMap;

//存放数据库内一行数据的容器，容器元素为每个域的值
typedef std::vector<Table_Data>					ROW;

//数据列表, 在使用简易查询接口时会一次性获取所有查询的数据。容器内元素为数据库内的一行数据
typedef std::vector<ROW>					ROWS;

#endif 