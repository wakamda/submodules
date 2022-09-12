///////////////////////////////////////////////////////////
//  Ctmysql.cpp
//  Original author: wakamda
//  Implementation of class Ctmysql 
///////////////////////////////////////////////////////////
#include<iostream>
#include<string>
#include "Ctmysql.h"
#include "../log/Log.h"

#define LOG_TAG "database"
using namespace std;


/************************************************************************
 *  config
************************************************************************/
ERR_CODE Ctmysql::SwitchDBType(TABLE_CODING_TYPE tablecodingtype){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);

    bool bresult = false;
	string stype;
	switch (tablecodingtype)
	{
	case GBK:{
        bresult = Query("set names gbk"); 
        stype = "gbk"; 
        break;
    }
	case UTF8:{
        bresult = Query("set names utf8");
        stype = "utf8";
        break;
    }
	case NOTYPE:{
        bresult = true;
        break;
    }   
	default:
        break;
	}
	ALOGV("switchtype to %s return %s", stype.c_str(), str_err_code[bresult ? ERR_SUCCESS : ERR_FAILED]);
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return bresult ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::SetMysqlOption(MSQL_OPT opt,const void *arg){
    if (!mysql)
	{
		ALOGE("Option failed:mysql is NULL" );
		return ERR_FAILED;
	}
	int re = mysql_options(mysql, (mysql_option)opt, arg);
	if (re != 0)
	{
		ALOGE("mysql_options failed!error is:%s" , mysql_error(mysql) );
		return ERR_FAILED;
	}
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::SetConnectTimeout(int sec){
    return SetMysqlOption(MSQL_OPT_CONNECT_TIMEOUT, &sec);
}

ERR_CODE Ctmysql::SetReconnect(bool isre){
	return SetMysqlOption(MSQL_OPT_RECONNECT, &isre);
}

ERR_CODE Ctmysql::Init(){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
    Finit();
    mysql=mysql_init(NULL);
    if(mysql==NULL)
    {
        ALOGE("mysql_init failed!");
        return ERR_FAILED;
    }
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
    return ERR_SUCCESS;
}

ERR_CODE Ctmysql::Finit(){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
	//have result
	if(this->result){
		//free result failed
		if(FreeResult()){
			return ERR_FAILED;
		}
	}
    if(mysql!=NULL)
    {
        mysql_close(mysql);
        mysql = NULL;
    }
	if(mysql!=NULL){
		ALOGE("mysql Finit failed!");
		return ERR_FAILED;
	}
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::connectdb(const char* host,const char* user,const char* passwd,const char* dbname,unsigned short port,unsigned long flag){   
    ALOGV(">>> %s", __PRETTY_FUNCTION__);
	if (!mysql && !Init())
	{
		ALOGE("Mysql connect failed! msyql is not init!");
		return ERR_FAILED;
	}
    mysql = mysql_real_connect(mysql, host, user, passwd, dbname, port, NULL, flag);
    if(mysql == NULL)
    {  
        ALOGE("Mysql connect failed!");
		return ERR_FAILED;  
    }  
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
    return ERR_SUCCESS;  
}

/***********************************************************************
 *  operation
************************************************************************/
bool Ctmysql::Query(const char*sql, unsigned long sqllen)
{
    if (!mysql)
	{
		ALOGE( "Query failed:mysql is NULL" );
		return false;
	}
    if (!sql)
	{
		ALOGE("sql is null" );
		return false;
	}
    if (sqllen <= 0)
        sqllen = (unsigned long)strlen(sql);
    if (sqllen <= 0)
	{
		ALOGE("Query sql is empty or wrong format!" );
		return false;
	}
    //Query
    int re =mysql_real_query(mysql, sql, sqllen);
    if (re != 0)
    {
        ALOGE("mysql_real_query failed! error is:%s" , mysql_error(mysql) );
        return false;
    }
    return true;
}

ERR_CODE Ctmysql::createdatabase(std::string &dbname){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
	//
    if(dbname.empty()){
        ALOGE("return %s" ,str_err_code[ERR_INVALID_ARG] );
        return ERR_INVALID_ARG;
    }
	//
    std::string queryStr = "create database if not exists `"+dbname+"`";
    if(!Query(queryStr.c_str(),0))
    {
        ALOGE("database %s create faield in create", dbname.c_str());
    	return ERR_FAILED;
    }
	queryStr = "use "+dbname;
    if(!Query(queryStr.c_str(),0))
    {
		ALOGE("database %s create faield in use", dbname.c_str());
    	return ERR_FAILED;
    }
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::deletedatabase(std::string &dbname){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
    if(dbname.empty()){
        ALOGE("return %s", str_err_code[ERR_INVALID_ARG]);
        return ERR_INVALID_ARG;
    }
    std::string queryStr = "drop database if exists `"+dbname+"`";
    if(!Query(queryStr.c_str(),0))
    {
		ALOGE("database %s delete faield or already exist", dbname.c_str());
    	return ERR_FAILED; 
    }
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
    return ERR_SUCCESS;
}

ERR_CODE Ctmysql::createtable(TABLEVECTOR &vector,std::string &tablename, TABLE_CODING_TYPE tablecodingtype){
    ALOGV(">>> %s", __PRETTY_FUNCTION__);
	if(vector.empty() || tablename.empty() || tablecodingtype > NOTYPE){
        ALOGV("%s", str_err_code[ERR_INVALID_ARG]);
        return ERR_INVALID_ARG;
    }
    string sql = "CREATE TABLE IF NOT EXISTS `" + tablename + "` (";
    TABLEVECTOR::iterator iter = vector.begin();
	for (;iter != vector.end(); ++iter)
	{
		sql += GetAutogenCreateSql(&(*iter));
		sql += ",";
	}
	sql[sql.size() - 1] = ' ';
	sql += ")";
	ALOGV("SQL = %s", sql.c_str());
	
	if(!Query(sql.c_str()))
	{
		ALOGE("%s", str_err_code[ERR_FAILED]);
        return ERR_FAILED;
	}
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::deletetable(std::string &tablename){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
    if (tablename.empty())
	{
		ALOGE("return %s",str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	string sql = "DROP TABLE IF EXISTS `" + tablename + "`";
	if(!Query(sql.c_str()))
	{
		ALOGE("%s", str_err_code[ERR_FAILED]);
        return ERR_FAILED;
	}
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::Insert(TableDataMap &da, std::string &tablename){

	//if(!SelectFromTable(tablename))
	//{
	//	Tprint("table %s is already here ", tablename);
	//	return ERR_INVALID_DATA;
	//}
    if (da.empty() || tablename.empty())
	{
		ALOGE("%s", str_err_code[ERR_INVALID_DATA]);
		return ERR_INVALID_DATA;
	}
	if (!mysql)
	{
		ALOGE("Insert failed:mysql is NULL");
		return ERR_FAILED;
	}
	string sql = GetAutogenInsertSql(da, tablename);
	if (sql.empty()){
		ALOGE("%s",str_err_code[ERR_FAILED]);
		return ERR_FAILED;
	}
	ALOGV("%s",sql.c_str());
	if (!Query(sql.c_str())){
		return ERR_FAILED;
	}
	uint64_t num = mysql_affected_rows(mysql);
	if (num <= 0)
		return ERR_FAILED;

	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::DeleteDataWithId(std::string &tablename, std::string &idname, std::string &idnum){
    //delete FROM A WHERE id = 'B' 
	if (tablename.empty() || idname.empty() || idnum.empty())
	{
		ALOGE("return %s", str_err_code[ERR_INVALID_DATA]);
		return ERR_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where " + idname + "=" + idnum;
	if (!Query(sql.c_str()))
	{
		ALOGE("delete faield in table:%s, col:%s, data:%s", tablename.c_str(), idname.c_str(), idnum.c_str());
		return ERR_FAILED;
	}
	ALOGE("delete success in table:%s, col:%s, data:%s", tablename.c_str(), idname.c_str(), idnum.c_str());
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::DeleteDataLikeWithFieldname(std::string &tablename, std::string &fieldname, std::string &fielddata){
    //DELETE from tablename where 字段名 like '%字段值%'
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		ALOGE("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where `" + fieldname + "` like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
	{
		ALOGE("drop faield in table:%s, col:%s, data:%s", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
		return ERR_FAILED;
	}
	ALOGV("drop success in table:%s, col:%s, data:%s", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
	return ERR_SUCCESS;
}

uint64_t Ctmysql::UpdateData(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum){
    if (da.empty() || tablename.empty() || where.empty())
	{
		ALOGE("return %s",str_err_code[ERR_INVALID_ARG]);
		return -1;
	}
	if (!mysql)return -1;
	string sql = GetAutogenUpdateSql(da, tablename, where, idnum);
	if (sql.empty())
		return -1;
	if (!Query(sql.c_str()))
	{
		ALOGE("return %s",str_err_code[ERR_FAILED]);
		return -1;
	}
	return mysql_affected_rows(mysql);
}

ERR_CODE Ctmysql::SelectFromTable(std::string &tablename){
	ALOGV(">>> %s",__PRETTY_FUNCTION__);
    if(tablename.empty())
        return ERR_INVALID_ARG;
    string sql = "select * from " + tablename;
	
	if(!Query(sql.c_str()))
	{
		ALOGE("%s",str_err_code[ERR_FAILED]);
		return ERR_FAILED;
	}
	ALOGV("<<< %s",__PRETTY_FUNCTION__);
    return ERR_SUCCESS;
}

ERR_CODE Ctmysql::SelectDataWithX(std::string &tablename, std::string &fieldname, std::string &fielddata){
    if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		ALOGV("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	return (Query(sql.c_str()) == true) ? ERR_SUCCESS : ERR_FAILED;
}

ERR_CODE Ctmysql::StoreResult(){
	ALOGV(">>> %s",__PRETTY_FUNCTION__);
    if (!mysql)
	{
		ALOGE("StoreResult failed:mysql is NULL" );
		return ERR_FAILED;
	}
	FreeResult();
	result = mysql_store_result(mysql);
	if (!result)
	{
		ALOGE("mysql_store_result failed!error is:%s", mysql_error(mysql));
		return ERR_FAILED;
	}
	ALOGV("<<< %s",__PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::UseResult(){
    if (!mysql)
	{
		ALOGE("UseResult failed:mysql is NULL");
		return ERR_FAILED;
	}
	FreeResult();
	result = mysql_use_result(mysql);
	if (!result)
	{
		ALOGE("mysql_use_result failed!erorr is:%s", mysql_error(mysql));
		return ERR_FAILED;
	}
	return ERR_SUCCESS;
}

ERR_CODE Ctmysql::FreeResult()
{
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
	mysql_free_result(result);
	result = NULL;
	if(this->result){
		ALOGE("mysql_free_result failed!");
		return ERR_FAILED;
	}
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

ROW Ctmysql::FetchRow(){
    ROW re;
	if (!result)
	{
		ALOGE("reult is null");
		return re;
	}
	//hang
	MYSQL_ROW row = mysql_fetch_row(result);
	if (!row)
	{
		ALOGW("row has been null or error");
		//return re;
	}


	//lie

	//unsigned int num_fields = mysql_num_fields(result);//lie 5
	//ALOGV("lie number:%d",num_fields);
	//unsigned long *lens = mysql_fetch_lengths(result);//size of each lie in one hang
	//for (unsigned int i = 0; i < num_fields; i++)
	//{
	//	Table_Data da;
	//	da.data = row[i];
	//	da.size = lens[i];
	//	//获取列的类型
	//	auto field = mysql_fetch_field_direct(result, i);
	//	da.type = (TABLE_DATA_TYPE)field->type;
	//	re.push_back(da);
	//}


	return re;
}
//简易接口,返回select的数据结果，每次调用清理上一次的结果集
ERR_CODE Ctmysql::EasySelect(std::string &tablename, ROWS &rows){
	ALOGV(">>> %s", __PRETTY_FUNCTION__);
	if (tablename.empty())
	{
		ALOGE("%s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	string sql = "select * from " + tablename;
	//free first
	if(FreeResult()){
		ALOGE("FreeResult failed");
		return ERR_FAILED;
	}
	if (!Query(sql.c_str()))
		return ERR_FAILED;

	if (StoreResult())
		return ERR_FAILED;

	ALOGV(">>> FetchRow()");
	//fetch one row each time
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	ALOGV("<<< FetchRow()");
	ALOGV("<<< %s", __PRETTY_FUNCTION__);
	return ERR_SUCCESS;
}

//模糊查询
ERR_CODE Ctmysql::EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, ROWS &rows){
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		ALOGE("return %s", str_err_code[ERR_INVALID_ARG]);
		return ERR_INVALID_ARG;
	}
	if(!FreeResult()){
		ALOGE("FreeResult failed");
		return ERR_FAILED;
	}
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
		return ERR_FAILED;
	if (StoreResult() != ERR_SUCCESS)
		return ERR_FAILED;
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	return ERR_SUCCESS;
}
/***********************************************************************
 * underlying operation
************************************************************************/
std::string Ctmysql::GetTableFieldTypeString(TABLE_FIELD_TYPE gbkorutf)
{
	std::string typestring = str_table_field_type[gbkorutf];
	return typestring;
}

std::string Ctmysql::GetAutogenCreateSql(LPTABLESTRUCT pfield)
{
	std::string fieldsql = "`" + pfield->field_name + "` ";
	fieldsql += GetTableFieldTypeString(pfield->field_type);
	if (pfield->field_len != 0)
	{
		fieldsql += "(";
		fieldsql += to_string(pfield->field_len);
		fieldsql += ")";
	}
	if (pfield->table_coding_type == GBK)
	{
		fieldsql += " CHARACTER SET gbk COLLATE gbk_bin";
	}
	else if (pfield->table_coding_type == UTF8)
	{
		fieldsql += " CHARACTER SET utf8 COLLATE utf8_bin";
	}
	else//NOTYPE才考虑是否将此字段设为自增ID
	{
		if (pfield->field_type == DBTYPE_ID)
		{
			fieldsql += ",PRIMARY KEY(`";
			fieldsql += pfield->field_name;
			fieldsql += "`)";
		}
	}
	return fieldsql;
}

std::string Ctmysql::GetAutogenInsertSql(TableDataMap &da, std::string &tablename){
    string sql = "";
	sql = "insert into `";
	sql += tablename;
	sql += "`";
	//insert into t_video (name,size) values("name1","1024")
	string keys = "";
	string vals = "";

	//迭代map
	for (TableDataMap::iterator ptr = da.begin(); ptr != da.end(); ptr++)
	{
		//字段名
		keys += "`";
		keys += ptr->first;
		keys += "`,";

		vals += "'";
		vals += ptr->second.data;
		vals += "',";
	}
	//去除多余的逗号
	keys[keys.size() - 1] = ' ';
	vals[vals.size() - 1] = ' ';

	sql += "(";
	sql += keys;
	sql += ")values(";
	sql += vals;
	sql += ")";
	return sql;
}

std::string Ctmysql::GetAutogenUpdateSql(TableDataMap &da, std::string &tablename, std::string &where, std::string &idnum){
    //update t_video set name='update001',size=1000 where id=10
	string sql = "";
	sql = "update `";
	sql += tablename;
	sql += "` set ";
	for (TableDataMap::iterator ptr = da.begin(); ptr != da.end(); ptr++)
	{
		sql += "`";
		sql += ptr->first;
		sql += "`='";
		sql += ptr->second.data;
		sql += "',";
	}
	//去除多余的逗号
	sql[sql.size() - 1] = ' ';
	sql += " where ";
	sql += where;
	sql += "=";
	sql += idnum;
	return sql;
}
