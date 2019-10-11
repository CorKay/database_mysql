#include "db_base.h"

//连接数据库
MYSQL* db_connect(const char* host, const char* user,
	const char* passwd, const char* db_name)
{
	//初始化
	MYSQL* mysql = (MYSQL*)malloc(sizeof(MYSQL));
	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		syslog(LOG_ERR, "Initlize MySQL failed\n");
		return NULL;
	}

	//连接
	if (!mysql_real_connect(mysql, host, user, passwd, db_name, 0, NULL, 0))
	{
		syslog(LOG_ERR, "Cannot connect to database\n");
		mysql_error(mysql);
		return NULL;
	}

	return mysql;
}
//获取数据库连接情况
MYSQL* db_get_connect(const char* host, const char* user,
	const char* passwd, const char* db_name)
{
	return db_connect(host, user, passwd, db_name);
}

//关闭数据库
int db_disconnect(MYSQL* mysql)
{
	if (mysql)
	{
		mysql_close(mysql);
		return 0;
	}
	syslog(LOG_ERR, "Disconnected mysql database.Mysql maybe null\n");
	return -1;
}
//获取数据库关闭情况
int db_get_disconnect(MYSQL* mysql)
{
	return db_disconnect(mysql);
}

//增 删 改
int db_change_query(MYSQL* mysql, const char* query)
{
	printf("query:%s \n", query);
	//语句执行结果
	if (mysql_query(mysql, query) != 0)
	{
		syslog(LOG_ERR, "Database query failed:%s[%s]\n", mysql_error(mysql), query);
		return -1;
	}
	
	printf("affected rows:%lld \n", mysql_affected_rows(mysql));

	return 0;
}

//查询
int db_select_query(MYSQL* mysql, const char* query)
{
	int affected_rows = 0;
	MYSQL_RES* sel_res;
	MYSQL_FIELD* sel_field;
	MYSQL_ROW    sel_row;

	unsigned long* lengths;
	int cols, i;

	//语句执行
	if (mysql_query(mysql, query) != 0)
	{
		syslog(LOG_ERR, "Database query failed:%s [%s]\n", mysql_error(mysql), query);
		return -1;
	}

	//判断是否执行select操作成功
	sel_res = mysql_store_result(mysql);
	if (NULL == sel_res)
	{
		syslog(LOG_ERR, "mysql_store_result() happened error:%s", mysql_error(mysql));
		return -1;
	}
	printf("num rows:%lld \n", mysql_num_rows(sel_res));

#if 1
	//后台打印查询结果
	cols = mysql_num_fields(sel_res);           //获取表的列数
	printf("num cols:%d \n", cols);

	sel_field = mysql_fetch_fields(sel_res);     //获取字段信息与类型
	for (i = 0; i < cols; i++)
	{
		printf("   info: %s   type: %d\t", sel_field[i].name, sel_field[i].type);
	}
	printf("\n");

	while (sel_row = mysql_fetch_row(sel_res))   //打印结果
	{
		for (i = 0; i < cols; i++)
		{
			lengths = mysql_fetch_lengths(sel_res);
			printf("%s(%lu)\t", sel_row[i], lengths[i]);
		}
		printf("\n");
	}
#endif

	mysql_free_result(sel_res);

}
