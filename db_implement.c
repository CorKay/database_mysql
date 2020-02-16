#include "db_base.h"
#include "db_implement.h"

//insert 接口
int implement_insert(const char* statement)
{
	MYSQL conn_mysql;
	int result_operate = 0;
	
	db_connect(&conn_mysql, TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);								//连接

	result_operate = db_operate(&conn_mysql, statement);													//执行

	db_disconnect(&conn_mysql);																				//断开

	if (result_operate != 0)
	{
		printf("Insert successful \n");
		syslog(LOG_DEBUG, "Insert Successful\n");
		return result_operate;
	}
	printf("Insert failed \n");
	syslog(LOG_ERR, "Insert Failed\n");
	return -1;

}

//delete 接口
int implement_delete(const char* statement)
{	
	MYSQL conn_mysql;
	int result_operate = 0;

	db_connect(&conn_mysql, TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);			//连接

	result_operate = db_operate(&conn_mysql, statement);								//执行

	db_disconnect(&conn_mysql);															//断开

	if (result_operate != 0)
	{
		printf("Delete successful \n");
		syslog(LOG_DEBUG, "Delete Successful\n");		
		return result_operate;
	}
	printf("Delete failed \n");
	syslog(LOG_ERR, "Delete Failed\n");
	return -1;
}

//update 接口
int implement_update(const char* statement)
{
	MYSQL conn_mysql;
	int result_operate = 0;

	db_connect(&conn_mysql, TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);								//连接

	result_operate = db_operate(&conn_mysql, statement);													//执行

	db_disconnect(&conn_mysql);																				//断开

	if (result_operate != 0)
	{
		printf("Update successful \n");
		syslog(LOG_DEBUG, "Update Successful\n");
		return result_operate;
	}
	printf("Update failed \n");
	syslog(LOG_ERR, "Update failed\n");
	return -1;
}

//select 接口
char* implement_select(const char* statement)
{
	MYSQL conn_mysql;
	MYSQL_RES* sel_ret = NULL;
	char* result_query = NULL;

	db_connect(&conn_mysql, TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);			//连接

	sel_ret = db_query(&conn_mysql, statement);											//执行

	db_disconnect(&conn_mysql);															//断开

	result_query = db_result_to_cJson(sel_ret);											//将结果集转为cJson字符串传递
	if (result_query != NULL)
	{
		printf("MYSQL_RESULT to cJSON_Array successful \n");
		return result_query;
	}
	printf("MYSQL_RESULT to cJSON_Array faild \n");
	return NULL;

	mysql_free_result(sel_ret);															//释放结果集
	sel_ret = NULL;

	return result_query;
}

//free接口
int implement_free(char* result)
{
	db_free_result(result);
	return 0;
}
