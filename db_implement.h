#ifndef _DB_IMPLEMENT_H
#define _DB_IMPLEMENT_H

#include "db_base.h"

//数据库属性
//test
#define TEST_HOST "localhost"
#define TEST_USER "root"
#define TEST_PASSWD "123"
#define TEST_DB_NAME "test"

//函数声明
int implement_insert(const char* statement);
int implement_delete(const char* statement);
int implement_update(const char* statement);
char* implement_select(const char* statement);
int implement_free(char* result);

#endif // !_DB_IMPLEMENT_H
