#ifndef _DB_BASE_H
#define _DB_BASE_H


//底层   :db_base
//		连接数据库
//		断开连接
//		增删改-- > 通用语句执行接口
//		查询-- > 语句执行接口, 与上一个参数不同, 并额外对语句执行返回的结果集做了提取
//		(后台打印查询结果print)
//业务层 :db_business
//		callback_get_某某_info
//		某某_table_insert
//		某某_table_delete
//		某某_table_update
//		某某_table_select


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <mysql/mysql.h>

//test
#define TEST_HOST "localhost"
#define TEST_USER "root"
#define TEST_PASSWD "123"
#define TEST_DB_NAME "test"

/*
 *用于存储表相应字段的对应结构体 以及
 *用于存储相应表格结果集各项属性的结构体(query_)
 *num_columns为字段个数
 *num_rows表示查询结果集中的行数
 *cur_row表示当前操作的行
 *最后一个表示对应表结构的结构体类型的指针，存储结果集的值
*/

//测试用表test_table信息
typedef struct test_table_info {
	int user_id;
	char names[20];
}test_info;

typedef struct query_test_info {
	int num_columns;
	int num_rows;
	int cur_row;
	test_info testInfo;
}query_test_info;




//函数声明
//db_base
MYSQL* db_connect(const char* host, const char* user, const char* passwd, const char* db_name);
void db_disconnect(MYSQL* mysql);
int db_change_query(MYSQL* mysql, const char* query);
int db_select_query(MYSQL* mysql, const char* query, int(*call_back)(void*, MYSQL_RES*, int, int), void* info);
int print_res(MYSQL* mysql, MYSQL_RES* res);

//db_business
//Insert
int test_table_insert(test_info* test);

//delete
int test_table_delete(test_info* test);

//Update
int test_table_update(test_info* test);

//Select
int test_table_select(query_test_info* query_test);


//各业务表对自身查询结果集的处理函数
//test
int callBack_get_test_info(void* arg, MYSQL_RES* result_sel, int num_fields, int num_rows);


#endif // !_DB_BASE_H
