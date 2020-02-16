#include "db_base.h"

#if 1
//test
//test_table Insert
int test_table_insert(test_info* test)
{
	int ret = 0;
	MYSQL* mysql;
	char* prep_query = "INSERT INTO %s (%s,%s) VALUES (%d,'%s')";

	char* exec_query = (char*)malloc(1024);
	if (exec_query == NULL)
	{
		printf("insert query malloc faild \n");
		return -1;
	}
	
	mysql = db_connect(TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);					//连接

	sprintf(exec_query, prep_query, "test_table", "user_id", "names", test->user_id, test->names);		//拼接语句

	ret = db_operate(mysql, exec_query, NULL);								//执行操作

	db_disconnect(mysql);											//断开

	free(exec_query);																					//释放句柄空间

	if (ret == 0)
	{
		printf("test_table Insert successful \n");
		return 0;
	}
	printf("test_table Insert failed \n");
	return -1;

}

//test_table Delete
int test_table_delete(test_info* test)
{
	int ret = 0;
	MYSQL* mysql;
	char* prep_query = "DELETE FROM %s WHERE %s=%d";
	char* exec_query[50] = { 0 };

	mysql = db_connect(TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);			//连接

	sprintf(exec_query, prep_query, "test_table", "user_id", test->user_id);		//拼接

	ret = db_operate(mysql, exec_query, NULL);						//执行操作

	db_disconnect(mysql);									//断开

	if (ret == 0)
	{
		printf("test_table Delete successful \n");
		return 0;
	}
	printf("test_table Delete failed \n");
	return -1;
}

//test_table Update
int test_table_update(test_info* test)
{
	int ret = 0;
	MYSQL* mysql;
	char* prep_query = "UPDATE %s SET %s='%s' WHERE %s=%d";

	char* exec_query = (char*)malloc(1024);
	if (exec_query == NULL)
	{
		printf("update query malloc faild \n");
		return -1;
	}

	mysql = db_connect(TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);					//连接

	sprintf(exec_query, prep_query, "test_table", "names", test->names, "user_id", test->user_id);		//拼接

	ret = db_operate(mysql, exec_query, NULL);								//执行操作

	db_disconnect(mysql);											//断开

	free(exec_query);																					//释放语句空间

	if (ret == 0)
	{
		printf("test_table Update successful \n");
		return 0;
	}
	printf("test_table Update failed \n");
	return -1;
}

//test_table Select
int test_table_select(MYSQL_RES** result)
{
	int ret = 0;
	MYSQL* mysql;
	char* prep_query = "SELECT * FROM %s";
	char* exec_query[30] = { 0 };

	mysql = db_connect(TEST_HOST, TEST_USER, TEST_PASSWD, TEST_DB_NAME);			//连接

	sprintf(exec_query, prep_query,"test_table");						//拼接

	ret = db_operate(mysql,exec_query,result);						//执行操作

	db_disconnect(mysql);									//断开

	if (ret == 0)
	{
		printf("test_table Select successful \n");
		return 0;
	}
	printf("test_table Select failed \n");
	return -1;
}

#endif
