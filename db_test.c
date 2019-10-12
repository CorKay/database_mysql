#include "db_base.h"

//Test
int main()
{
	const char* host = "localhost";
	const char* user = "root";
	const char* passwd = "123";
	const char* db_name = "test";

	char* prep_ins_query = "INSERT INTO test_table (%s) VALUES (%s)";
	char insert_query[512] = { 0 };

	char* prep_sel_query = "SELECT * from %s";
	char select_query[256] = { 0 };

	MYSQL* mysql = db_get_connect(host, user, passwd, db_name);						//连接
	if (mysql == NULL)
	{
		printf("db_connect failed \n");
		syslog(LOG_ERR, "db_connect failed\n");
		return 0;
	}

	sprintf(insert_query, prep_ins_query, "names", "'WangMing'");						//拼接插入语句

	sprintf(select_query, prep_sel_query, "test_table");							//拼接查询语句

	db_change_query(mysql, insert_query);									//插入

	db_select_query(mysql, select_query);									//查询

	db_select_query(mysql, "UPDATE test_table set names = 'Susan' where user_id = 4");			//修改

	db_select_query(mysql, select_query);									//查询

	db_disconnect(mysql);											//断开连接

	return 0;
}
