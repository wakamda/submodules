# database-moudle

API:

```c++

config:

//数据库操作模块初始化
bool dbomInit();

//模块退出，内存清除
ERR_CODE dbomUnInit();

//连接数据库
ERR_CODE dbomConnectdb(const char* host,const char* user,const char* pwd,const char* db_name,unsigned short port,unsigned long flag = 0);

选择
ERR_CODE dbomSwitchDBType(TABLE_CODING_TYPE type = UTF8);


ERR_CODE dbomSetMysqlOption(MSQL_OPT opt,const void *arg);

设置数据库连接timeout时间
ERR_CODE dbomSetConnectTimeout(int sec);

设置重新连接数据库
ERR_CODE dbomSetReconnect(bool isre);

获取数据库host
char* dbomGethost();

设置数据库host
char* dbomSethost(char* newVal);

...

operation:

//数据库操作基础接口
bool dbomQuery(const char*sql, unsigned long sqllen = 0);

//创建数据库
ERR_CODE dbomcreatedatabase(std::string dbname);

//删除数据库
ERR_CODE dbomdeletedatabase(std::string dbname);

//创建表
ERR_CODE dbomcreatetable(TABLEVECTOR &vector,std::string tablename, TABLE_CODING_TYPE tablecodingtype = UTF8);

//删除表
ERR_CODE dbomdeletetable(std::string tablename);

//插入一条数据
ERR_CODE dbomInsert(TableDataMap &da, std::string tablename);

//删除一条数据
ERR_CODE dbomDeleteDataWithId(std::string tablename, std::string idname, std::string idnum);

......

```