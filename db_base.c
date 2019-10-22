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

//查询接口(句柄,结果集处理函数(返回结果类型,结果集,字段数,行数),查询语句,结果类型)
int db_select_query(MYSQL* mysql, const char* query, int(*call_back)(void*, MYSQL_RES*, int, int), void* info)
{
	MYSQL_RES* sel_res = NULL;

	int num_fields = 0;
	int num_rows = 0;

	printf("sql_query : %s \n", query);

	//语句执行
	if (mysql_query(mysql, query) != 0)
	{
		printf("Query ERRO \n");
		syslog(LOG_ERR, "Database query failed:%s [%s]\n", mysql_error(mysql), query);
		return -1;
	}

	//判断是否执行select操作成功,并返回结果集
	sel_res = mysql_store_result(mysql);
	if (NULL == sel_res)
	{
		printf("select ERRO \n");
		syslog(LOG_ERR, "mysql_store_result() happened error:%s", mysql_error(mysql));
		return -1;
	}
	printf("Select Successful \n");
//	print_res(mysql, sel_res);

	num_fields = mysql_num_fields(sel_res);
	num_rows = mysql_num_rows(sel_res);

	call_back(info, sel_res, num_fields, num_rows);		//处理返回结果集
	
	mysql_free_result(sel_res);							//释放结果集

	return 0;
}

//后台打印结果集
int print_res(MYSQL* mysql, MYSQL_RES* res)
{
	MYSQL_FIELD* sel_field;								//结果集的字段信息
	MYSQL_ROW sel_row;									//结果集字段的行数

	int cols, rows, i;

	cols = mysql_num_fields(res);				//获取表的列数

	//后台打印查询结果

	printf("*******************SELECT RESULT*******************\n");

	sel_field = mysql_fetch_fields(res);		//获取字段信息与类型
	for (i = 0; i < cols; i++)
	{
		printf("%s(type:%d)\t", sel_field[i].name, sel_field[i].type);
	}
	printf("\n");

	while (sel_row = mysql_fetch_row(res))		//打印结果
	{
		for (i = 0; i < cols; i++)
		{
			printf("%s\t", sel_row[i]);
		}
		printf("\n");
	}

	return 0;
}
