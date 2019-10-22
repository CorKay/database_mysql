#ifndef _DB_BASE_H
#define _DB_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <mysql/mysql.h>

//数据库属性
//test
#define TEST_HOST "localhost"
#define TEST_USER "root"
#define TEST_PASSWD "123"
#define TEST_DB_NAME "test"

//用于存储表相应字段的结构体,用于测试传值
//test_table
typedef struct test_table_info {
	int user_id;
	char names[20];
}test_info;

//函数声明
//db_base
MYSQL* db_connect(const char* host, const char* user, const char* passwd, const char* db_name);
void db_disconnect(MYSQL* mysql);
int db_operate(MYSQL* mysql, const char* query, MYSQL_RES** result);
void db_free_select_result(MYSQL_RES **sel_result);
int print_res(MYSQL_RES* res);

//db_business
//test
int test_table_insert(test_info* test);
int test_table_delete(test_info* test);
int test_table_update(test_info* test);
int test_table_select(MYSQL_RES** result);

#endif // !_DB_BASE_H
