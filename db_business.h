#ifndef _DB_BUSINESS_H
#define _DB_BUSINESS_H

#include "db_base.h"
#include "db_implement.h"

//用于存储业务表相应字段的结构体,用于测试传值
//test_table
typedef struct test_table_info {
	int user_id;
	char names[20];
}test_info;

//函数声明
//db_business
int business_free(char* result);
//test
int test_table_insert(test_info* test);
int test_table_delete(test_info* test);
int test_table_update(test_info* test);
char* test_table_select();



#endif // _DB_BUSINESS_H
