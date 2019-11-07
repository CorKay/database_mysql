#include "db_base.h"

//test call_back
int callBack_get_test_info(void* arg, MYSQL_RES* result_sel, int num_fields, int num_rows)
{
	MYSQL_ROW row;

	query_test_info* result = (query_test_info*)arg;
	if (result == NULL)
	{
		printf("Reference ERRO \n");
		return -1;
	}

	printf("num_fields:%d,num_rows:%d\n", num_fields, num_rows);	//打印结果集字段数和行数

	/*if (result && (&result->testInfo == NULL) && num_fields > 0 && num_rows > 0)
	{
		result->testInfo = (test_info*)malloc(num_rows * sizeof(test_info));
		if (NULL == result->testInfo)
		{
			syslog(LOG_ERR, "malloc failed.\n");
			return -1;
		}
		printf("malloc successful \n");
		memset(result->testInfo, 0, num_rows * sizeof(test_info));

		result->num_columns = num_fields;
		result->num_rows = num_rows;
		result->cur_row = 0;
	}*/

	result->num_columns = num_fields;
	result->num_rows = num_rows;
	result->cur_row = 0;

	printf("*******************SELECT RETURN RESULT*******************\n");
	//将查询到的结果集根据表的字段信息返回给相应的结构体
	if (&result->testInfo != NULL && result->cur_row < result->num_columns)
	{
		while ((row = mysql_fetch_row(result_sel)) != NULL)
		{
			printf("cur_rows :%d\n", result->cur_row);
			if (row[0])
			{
				result->testInfo.user_id = atoi(row[0]);
			}
			else
			{
				result->testInfo.user_id = 0;
			}
			if (row[1])
			{
				strcpy(&result->testInfo.names,row[1]);
			}
			else
			{
				strcpy(&result->testInfo.names,"nobody");
			}
			printf("UserID:%d \t",&result->testInfo.user_id);
			printf("Name:%s \n", &result->testInfo.names);
			result->cur_row ++;
		}
		return 0;
	}
	return -1;
}