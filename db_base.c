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
	printf("Malloc successful,mysql is %p \n", mysql);

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
}

//增 删 改 接口
int db_change_query(MYSQL* mysql, const char* query)
{
	printf("sql_query : %s \n", query);
	
	//语句执行结果
	if (mysql_query(mysql, query) != 0)
	{
		printf("Query ERRO \n");
		syslog(LOG_ERR, "Database query failed:%s[%s]\n", mysql_error(mysql), query);
		return -1;
	}

	//打印表中变化的行数
	printf("affected rows:%lld \n", mysql_affected_rows(mysql));

	return 0;
}

//查询 接口
MYSQL_ROW* db_select_query(MYSQL* mysql, const char* query)
{
	int affected_rows = 0;
	MYSQL_RES* sel_res;
	MYSQL_FIELD* sel_field;
	MYSQL_ROW*   sel_row;

	int cols, i;
	
	printf("sql_query : %s \n", query);

	//语句执行
	if (mysql_query(mysql, query) != 0)
	{
		printf("Query ERRO \n");
		syslog(LOG_ERR, "Database query failed:%s [%s]\n", mysql_error(mysql), query);
		return NULL;
	}

	//判断是否执行select操作成功
	sel_res = mysql_store_result(mysql);
	if (NULL == sel_res)
	{
		syslog(LOG_ERR, "mysql_store_result() happened error:%s", mysql_error(mysql));
		return NULL;
	}

	printf("Select Successful \n");
	printf("num rows:%lld \n", mysql_num_rows(sel_res));

#if 1
	//后台打印查询结果
	cols = mysql_num_fields(sel_res);           //获取表的列数
	printf("num cols:%d \n", cols);

	sel_field = mysql_fetch_fields(sel_res);     //获取字段信息与类型
	for (i = 0; i < cols; i++)
	{
		printf("%s(type:%d)\t", sel_field[i].name, sel_field[i].type);
	}
	printf("\n");

	while (sel_row = mysql_fetch_row(sel_res))   //打印结果
	{
		for (i = 0; i < cols; i++)
		{
			printf("%s\t", sel_row[i]);
		}
		printf("\n");
	}
#endif

	mysql_free_result(sel_res);

	return sel_row;
}
