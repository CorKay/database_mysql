#include "db_base.h"

//连接数据库
MYSQL* db_connect(const char* host, const char* user, const char* passwd, const char* db_name)
{
	//初始化
	MYSQL* mysql = (MYSQL*)malloc(sizeof(MYSQL));
	if (mysql == NULL)
	{
		printf("malloc failed \n");
		return NULL;
	}
	printf("mysql malloc successful,mysql is %p \n", mysql);

	mysql = mysql_init(mysql);
	if (mysql == NULL)
	{
		syslog(LOG_ERR, "Initlize MySQL failed\n");
		free(mysql);
		return NULL;
	}
	printf("Init successful : mysql is %p \n", mysql);

	//连接
	printf("Connecting \n");
	if (!mysql_real_connect(mysql, host, user, passwd, db_name, 0, NULL, 0))
	{
		printf("Connect ERRO \n");
		syslog(LOG_ERR, "Cannot connect to database\n");
		mysql_error(mysql);
		free(mysql);
		return NULL;
	}
	printf("Connect successful : mysql is %p \n", mysql);

	return mysql;
}

//关闭数据库
void db_disconnect(MYSQL* mysql)
{
	mysql_close(mysql);
	free(mysql);
	printf("Disconnect~ ~ \n");
}

//数据库操作接口
int db_operate(MYSQL* mysql, const char* query, MYSQL_RES** result)
{
	printf("sql_query : %s \n", query);

	int affected_rows = 0;
	MYSQL_RES* sel_ret = NULL;

	//语句执行
	if (mysql_query(mysql, query) != 0)
	{
		printf("Query ERRO \n");
		syslog(LOG_ERR, "Database query failed:%s[%s]\n", mysql_error(mysql), query);
		return -1;
	}
	printf("query successful \n");

	if (mysql_field_count(mysql) > 0)						//判断是否执行的是查询语句
	{
		if (!(sel_ret = mysql_store_result(mysql)))				//取出结果集
		{
			printf("mysql_store_result ERRO \n");
			syslog(LOG_ERR, "mysql_store_result() happened error:%s", mysql_error(mysql));
			return -1;
		}

		if (mysql_num_rows(sel_ret) != 0)
		{
			if (result == NULL)
			{
				mysql_free_result(sel_ret);
			}
			else
			{
				*result = sel_ret;					//返回查询结果
			}
			return 0;
		}
		else
		{
			if (result == NULL)
			{
				mysql_free_result(sel_ret);
			}
			else
			{
				*result = sel_ret;
				sel_ret = NULL;
			}
			return -1;
		}
	}
	else
	{
		affected_rows = mysql_affected_rows(mysql);
		printf("affected rows:%lld \n", mysql_affected_rows(mysql));		//打印表中变化的行数
		return 0;
	}
}

//释放结果集内存
void db_free_select_result(MYSQL_RES** sel_result)
{
	MYSQL_RES* prep_result = NULL;

	if (sel_result != NULL)
	{
		prep_result = *sel_result;
		if (prep_result != NULL)
		{
			mysql_free_result(prep_result);
			prep_result = NULL;
			*sel_result = prep_result;
		}
	}
}

//打印结构集
int print_res(MYSQL_RES* res)
{
	MYSQL_FIELD* sel_field;								//结果集的字段信息
	MYSQL_ROW sel_row;								//结果集字段的行数

	int cols, rows, i;

	cols = mysql_num_fields(res);							//获取表的列数

	//后台打印查询结果

	printf("*******************SELECT RESULT*******************\n");

	sel_field = mysql_fetch_fields(res);						//获取字段信息与类型
	for (i = 0; i < cols; i++)
	{
		printf("%s(type:%d)\t", sel_field[i].name, sel_field[i].type);
	}
	printf("\n");

	while (sel_row = mysql_fetch_row(res))						//打印结果
	{
		for (i = 0; i < cols; i++)
		{
			printf("%s\t", sel_row[i]);
		}
		printf("\n");
	}

	return 0;
}
