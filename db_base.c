#include "db_base.h"

//连接数据库
MYSQL* db_connect(MYSQL* mysql, const char* host, const char* user, const char* passwd, const char* db_name)
{
	mysql_init(mysql);																//初始化
	if (mysql == NULL)
	{
		printf("Init ERRO \n");
		syslog(LOG_ERR, "Initlize MySQL failed\n");
		return NULL;
	}
	printf("Init successful : mysql is %p \n", mysql);

	if (!mysql_real_connect(mysql, host, user, passwd, db_name, 0, NULL, 0))		//连接
	{
		printf("Connect ERRO,error_info: %s \n",mysql_error(mysql));
		syslog(LOG_ERR, "Cannot connect to database\n");
		return NULL;
	}
	printf("Connect successful : mysql is %p \n", mysql);

	return mysql;
}

//断开连接
void db_disconnect(MYSQL* mysql)
{
	mysql_close(mysql);
	printf("Disconnect~ ~ \n");
}

//数据库操作
int db_operate(MYSQL* mysql, const char* statement)
{
	int affected_rows = 0;

	printf("sql_statement : %s \n", statement);			//语句执行
	if (mysql_query(mysql, statement) != 0)
	{
		printf("Operate ERRO \n");
		syslog(LOG_ERR, "Database operate failed:%s[%s]\n", mysql_error(mysql), statement);
		return -1;
	}
	printf("operate successful \n");

	affected_rows = mysql_affected_rows(mysql);
	printf("affected rows:%lld \n", affected_rows);		//打印表中变化的行数
	return affected_rows;
}

//数据库查询
MYSQL_RES* db_query(MYSQL* mysql, const char* statement)
{
	MYSQL_RES* sel_ret = NULL;

	printf("sql_statement : %s \n", statement);					//语句执行
	if (mysql_query(mysql, statement) != 0)
	{
		printf("Query ERRO \n");
		syslog(LOG_ERR, "Database query failed:%s[%s]\n", mysql_error(mysql), statement);
		return NULL;
	}
	printf("query succefful \n");

	if (!(sel_ret = mysql_store_result(mysql)))					//取出结果集
	{
		printf("mysql_store_result ERRO \n");
		syslog(LOG_ERR, "mysql_store_result() happened error:%s", mysql_error(mysql));
		return NULL;
	}

	return sel_ret;
}

//MySQL_Result To JsonArray
char* db_result_to_cJson(MYSQL_RES* res)
{
	char* res_cjson = NULL;
	cJSON* json_array;

	int cols, rows, i;
	MYSQL_FIELD* res_field;
	MYSQL_ROW res_row;
	
	json_array = cJSON_CreateArray();

	cols = mysql_num_fields(res);
	rows = mysql_num_rows(res);

	res_field = mysql_fetch_fields(res);

	while (res_row = mysql_fetch_row(res))
	{
		for (i = 0; i < cols; i++)
		{
			cJSON* array_item = cJSON_CreateObject();
			cJSON_AddStringToObject(array_item, res_field[i].name, res_row[i]);
			cJSON_AddItemToArray(json_array, array_item);
		}
	}

	res_cjson = cJSON_Print(json_array);

	cJSON_Delete(json_array);

	if (NULL == res_cjson)
	{
		return NULL;
	}
	
	printf("MYSQL_RESULT to cJSON_Array :\n%s\n", res_cjson);
	return res_cjson;	
}

//cJSON_free(指向json字符串的指针)
int db_free_result(char* result)
{
	cJSON_free(result);
	result = NULL;
	return 0;
}


//打印结果集,调试时使用
int db_print_res(MYSQL_RES* res)
{
	MYSQL_FIELD* sel_field;								//结果集的字段信息
	MYSQL_ROW sel_row;									//结果集字段的行数

	int cols, rows, i;

	cols = mysql_num_fields(res);						//获取表的列数
	rows = mysql_num_rows(res);							//获取表的行数

	//后台打印查询结果

	printf("*******************SELECT RESULT*******************\n");

	sel_field = mysql_fetch_fields(res);
	for (i = 0; i < cols; i++)
	{
		printf("%s(type:%d)\t", sel_field[i].name, sel_field[i].type);		//字段
	}
	printf("\n");

	while (sel_row = mysql_fetch_row(res))
	{
		for (i = 0; i < cols; i++)
		{
			printf("%s\t", sel_row[i]);										//值
		}
		printf("\n");
	}

	return 0;
}
