///////////////////////////////////////////////////////////
//  Ctmysql_api.h
//  Original author: wakamda
//  Implements file of the Ctmysql SDK API
///////////////////////////////////////////////////////////
#include "dbom_api.h"


int SetLogLevel(int level){
     return log_set_level((Log_Level_t)level);
}

int GetLogLevel(void){
     return log_get_level();
}

//创建句柄
bool sdk_Init(){
    Basic_db* instance = new Ctmysql();
    handle = reinterpret_cast<void*>(instance);
    instance->Init();
    return true;//reinterpret_cast<TMYSQL_HANDLE>(instance);
}

//销毁句柄
ERR_CODE sdk_Finit(){
    //创建一个新的局部指针变量，并将对象指针的值赋给它
    Basic_db *phandle = reinterpret_cast<Ctmysql*>(handle);
	phandle->Finit();
    //delete表示删除了该指针指向的值，也就是在init函数中 在堆中new出的对象的空间，达到目的，删除堆内空间，将全局指针变量设置为null，且推出后栈内为空
	delete phandle;
	handle = NULL;
	printf("release instance success handle = %p\n", handle);
	return ERR_SUCCESS;
}

ERR_CODE sdk_connectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag){
    return ((Basic_db*)handle)->connectdb(host, user, pwd, db_name,port,flag);
}

ERR_CODE sdk_SwitchDBType(TABLE_CODING_TYPE type){
    return ((Basic_db*)handle)->SwitchDBType(type);
}

ERR_CODE sdk_SetMysqlOption(MSQL_OPT opt,const void* arg){
    return ((Basic_db*)handle)->SetMysqlOption(opt,arg);
}

ERR_CODE sdk_SetConnectTimeout(int sec){
    return ((Basic_db*)handle)->SetConnectTimeout(sec);
}

ERR_CODE sdk_SetReconnect(bool isre){
    return ((Basic_db*)handle)->SetReconnect(isre);
}

char* sdk_Gethost(){
    return ((Basic_db*)handle)->Gethost();
}

char* sdk_Sethost(char* newVal){
    return ((Basic_db*)handle)->Sethost(newVal);
}

char* sdk_Getuser(){
    return ((Basic_db*)handle)->Getuser();
}

char* sdk_Setuser(char* newVal){
    return ((Basic_db*)handle)->Setuser(newVal);
}

char* sdk_Getpwd(){
    return ((Basic_db*)handle)->Getpwd();
}

char* sdk_Setpwd(char* newVal){
    return ((Basic_db*)handle)->Setpwd(newVal);
}

char* sdk_Getdbname(){
    return ((Basic_db*)handle)->Getdbname();
}

char* sdk_Setdbname(char* newVal){
    return ((Basic_db*)handle)->Setdbname(newVal);
}

unsigned short sdk_Getport(){
    return ((Basic_db*)handle)->Getport();
}

unsigned short sdk_Setport(unsigned short newVal){
    return ((Basic_db*)handle)->Setport(newVal);
}

unsigned long sdk_Getflag(){
    return ((Basic_db*)handle)->Getflag();
}

unsigned long sdk_Setflag(unsigned long newVal){
    return ((Basic_db*)handle)->Setflag(newVal);
}

/************************************************************************
 *  operation
************************************************************************/

bool sdk_Query(const char* sql, unsigned long sqllen){
    return ((Basic_db*)handle)->Query(sql,sqllen);
}

ERR_CODE sdk_createdatabase(std::string dbname){
    return ((Basic_db*)handle)->createdatabase(dbname);
}

ERR_CODE sdk_deletedatabase(std::string dbname){
    return ((Basic_db*)handle)->deletedatabase(dbname);
}

ERR_CODE sdk_createtable(TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype){
    return ((Basic_db*)handle)->createtable(vector, tablename, tablecodingtype);
}

ERR_CODE sdk_deletetable(std::string tablename){
    return ((Basic_db*)handle)->deletetable(tablename);
}

ERR_CODE sdk_Insert(TableDataMap &da, std::string tablename){
    return ((Basic_db*)handle)->Insert(da,tablename);
}

ERR_CODE sdk_DeleteDataWithId(std::string tablename, std::string idname, std::string idnum){
    return ((Basic_db*)handle)->DeleteDataWithId(tablename,idname,idnum);
}

ERR_CODE sdk_DeleteDataLikeWithFieldname(std::string tablename, std::string fieldname, std::string fielddata){
    return ((Basic_db*)handle)->DeleteDataLikeWithFieldname(tablename,fieldname,fielddata);
}

uint64_t sdk_UpdateData(TableDataMap &da, std::string tablename, std::string where, std::string idnum){
    return ((Basic_db*)handle)->UpdateData(da,tablename,where,idnum);
}

ERR_CODE sdk_SelectFromTable(std::string tablename){
    return ((Basic_db*)handle)->SelectFromTable(tablename);
}

ERR_CODE sdk_SelectDataWithX(std::string tablename, std::string fieldname, std::string fielddata){
    return ((Basic_db*)handle)->SelectDataWithX(tablename,fieldname,fielddata);
}

ERR_CODE sdk_StoreResult(){
    return ((Basic_db*)handle)->StoreResult();
}

ERR_CODE sdk_UseResult(){
    return ((Basic_db*)handle)->UseResult();
}

ERR_CODE sdk_FreeResult(){
    return ((Basic_db*)handle)->FreeResult();
}

ROW sdk_FetchRow( ROW &row){
    return ((Basic_db*)handle)->FetchRow();
}

ERR_CODE sdk_EasySelect(std::string tablename, ROWS &rows){
    return ((Basic_db*)handle)->EasySelect(tablename,rows);
}

ERR_CODE sdk_EasyLike(std::string tablename, std::string fieldname,std::string fielddata, ROWS &rows){
    return ((Basic_db*)handle)->EasyLike(tablename,fieldname,fielddata,rows);
}