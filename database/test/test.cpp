#include "../src/api/database_operate_moudle_api.h"
#include <iostream>
#include <unistd.h>

using namespace std;
//static TMYSQL_HANDLE _handle_ = NULL;

int parse_opt(int argc,  char * const argv[]){
	int c;
	while ((c = getopt (argc, argv, "v")) != -1){
		switch (c){
			case 'v':
				SetLogLevel( GetLogLevel() - 1 );
				break;
			default:
				break;
		}

	}
	return 0;
}

bool sdkInit(){
    sdk_Init();
    
    char arr_host[20]= "localhost";
    char arr_usr[20]= "root";
    char arr_pwd[20]= "123456";
    char arr_dbname[20]="mysql";
    ERR_CODE ret = sdk_connectdb(sdk_Sethost(arr_host),sdk_Setuser(arr_usr),sdk_Setpwd(arr_pwd),sdk_Setdbname(arr_dbname),sdk_Setport(3306),sdk_Setflag(0));
    if(ret == ERR_SUCCESS)
        return true;
    else{
        cout << "connect mysql failded!" << endl;
        return false;
    }
}

bool create_table(std::string st){

    TABLEVECTOR mytable;
    TABLESTRUCT a0;
    a0.field_name = "ID";
    a0.field_type = DBTYPE_ID;
    a0.table_coding_type = NOTYPE;
    mytable.push_back(a0);

    TABLESTRUCT a1;
	a1.field_name = "filetype";
	a1.field_type = DBTYPE_VARCHAR;
	a1.table_coding_type = GBK;
	a1.field_len = 128;
	mytable.push_back(a1);

    TABLESTRUCT a2;
	a2.field_name = "fieldata";
	a2.field_type = DBTYPE_VARCHAR;
	a2.field_len = 1024;
	mytable.push_back(a2);

	TABLESTRUCT a3;
	a3.field_name = "shuoming";
	a3.field_type = DBTYPE_VARCHAR;
	a3.field_len = 128;
	mytable.push_back(a3);

	TABLESTRUCT a4;
	a4.field_name = "shuoming2";
	a4.field_type = DBTYPE_VARCHAR;
	a4.field_len = 128;
	mytable.push_back(a4);

    ERR_CODE  re = sdk_createtable(mytable,st);
    if (re == ERR_SUCCESS)
	{
		cout << "create testdb success" << endl;
		return true;
	}
	else
	{
		cout << "create testdb failed" << endl;
		return false;
	}

	
}

bool insertdata(std::string tb){
    ERR_CODE ret;
	if(sdk_SwitchDBType( UTF8)){	
		return -1;
	}

	for (int i = 0; i < 2; ++i)
	{
		
		TableDataMap k;
		k["filetype"] = "文字";
		char szbufp[12] = { 0 };
		sprintf(szbufp, "%d", i);
		k["fieldata"] = szbufp;
		k["shuoming"] = "shuoming111";
		k["shuoming2"] = "shuoming222";

		ret = sdk_Insert( k, tb);
		if(ret)break;
	}
	if (ret)
	{
		cout << "insert data failed" << endl;
		return false;
	}

	ROWS rows;
	sdk_EasySelect( tb, rows);
	rows.begin();
	for (auto row : rows)
	{
		//遍历每一列
		for (auto c : row)
		{
			if (c.data) 
				cout << c.data << " ";
		}
		cout << endl;
	}

}

void updatedata(std::string tb)
{
	TableDataMap k2;
	k2["filetype"] = "文字";
	char szbufp[12] = { 0 };
	sprintf(szbufp, "%d", 6666);
	k2["fieldata"] = szbufp;
	k2["shuoming"] = "shuoming111";
	k2["shuoming2"] = "shuoming222";
	uint64_t ret = sdk_UpdateData( k2, tb, "ID", "2");
	
	sdk_SelectFromTable( tb);
	sdk_StoreResult();
	while (true)
	{
		ROW rowdata;
		sdk_FetchRow( rowdata);
		if (rowdata.empty())
		{
			break;
		}
		ROW::iterator iter = rowdata.begin();
		for (; iter != rowdata.end(); ++iter)
		{
			cout << (*iter).data << " ";
		}
		cout << endl;
	}
	sdk_FreeResult();
	if (ret > 0)
	{
		cout << "*********************************update data success*********************************" << endl;
		cout << "*********************************I change the date in ID9*********************************" << endl;
	}
	else
	{
		cout << "*********************************update data failed*********************************" << endl;
	}
}

int main(int argc, char * const argv[]){
	SetLogLevel(LOG_ERROR);
	parse_opt(argc, argv);

    std::string db = "test1db";
	std::string tb = "testtable";
	
	//
    if(!sdkInit()){
        return -1;
    }

	//delete testdb
#if 1
    ERR_CODE ret = sdk_deletedatabase(db);
    if(ret != ERR_SUCCESS){
		return -1;
    }
    else
        cout << "delete database success " << endl;
#endif 

#if 1
	//create_database
    ERR_CODE ret2 = sdk_createdatabase(db);
    if(ret2 != ERR_SUCCESS){
		return -1;
    }
    else
        cout << "cerate database success " << endl;
#endif

#if 0
	sdk_deletetable(tb);
#endif

#if 1
	//create table
	if(!create_table(tb))
		return -1;
#endif

#if 1
//
	insertdata(tb);

#endif

	updatedata(tb);
    sdk_Finit();

    return 0;
}