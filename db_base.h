#ifndef _DB_BASE_H
#define _DB_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <mysql/mysql.h>

//底层数据库操作函数接口
MYSQL* db_connect(const char* host, const char* user, const char* passwd, const char* db_name);
MYSQL* db_get_connect(const char* host, const char* user, const char* passwd, const char* db_name);
int db_disconnect(MYSQL* mysql);
int db_get_disconnect(MYSQL* mysql);
int db_change_query(MYSQL* mysql, const char* query);
int db_select_query(MYSQL* mysql, const char* query);

#endif // !_DB_BASE_H
