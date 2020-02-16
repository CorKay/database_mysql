#include "db_base.h"
#include "db_implement.h"
#include "db_business.h"

//释放结果集内存空间
int business_free(char* result)
{
	implement_free(result);
	return 0;
}

#if 1
/*
 * test_table(测试表),有两个字段
 * id 和 names
 * 这里模拟的业务层将针对这两个字段的值进行操作
 */
//test_table Insert
int test_table_insert(test_info* test)
{
	char* temp_statement = "INSERT INTO test_table (%s,%s) VALUES (%d,'%s')";
	char* exec_statement = (char*)malloc(sizeof(test_info) + strlen(temp_statement));
	if (exec_statement == NULL)
	{
		syslog(LOG_ERR, "Insert statement malloc faild\n");
		printf("Insert statement malloc faild \n");
		return -1;
	}

	sprintf(exec_statement, temp_statement,"user_id", "names", test->user_id, test->names);		//拼接语句

	implement_insert(exec_statement);															//执行

	SAFE_FREE(exec_statement);																	//释放语句空间

	return 0;
}

//test_table Delete
int test_table_delete(test_info* test)
{
	char* temp_statement = "DELETE FROM test_table WHERE %s=%d";
	char* exec_statement = (char*)malloc(sizeof(test_info) + strlen(temp_statement));
	if (exec_statement == NULL)
	{
		syslog(LOG_ERR, "Delete statement malloc faild\n");
		printf("Delete statement malloc faild \n");
		return -1;
	}

	sprintf(exec_statement, temp_statement, "user_id", test->user_id);					//拼接

	implement_delete(exec_statement);													//执行

	SAFE_FREE(exec_statement);															//释放语句空间

	return 0;
}

//test_table Update
int test_table_update(test_info* test)
{
	char* temp_statement = "UPDATE test_table SET %s='%s' WHERE %s=%d";
	char* exec_statement = (char*)malloc(sizeof(test_info) + strlen(temp_statement));
	if (exec_statement == NULL)
	{
		syslog(LOG_ERR, "Update statement malloc faild\n");
		printf("Update statement malloc faild \n");
		return -1;
	}

	sprintf(exec_statement, temp_statement, "names", test->names, "user_id", test->user_id);				//拼接

	implement_update(exec_statement);																		//执行			

	SAFE_FREE(exec_statement);																				//释放语句空间

	return 0;
}

//test_table Select
char* test_table_select()
{
	char* result = NULL;
	char* exec_statement = "SELECT * FROM test_table";

	result = implement_select(exec_statement);																//执行操作

	if (NULL == result)
	{
		printf("result to cJSON return faild \n");
		return NULL;
	}

	return result;
}

#endif
