#ifndef _DB_BASE_H
#define _DB_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <mysql/mysql.h>
#include "cJSON.h"
#include <math.h>
#include <limits.h>
#include <ctype.h>

#define SAFE_FREE(ptr) do{free(ptr); ptr = NULL;} while(0)

//函数声明
//db_base
MYSQL* db_connect(MYSQL* mysql, const char* host, const char* user, const char* passwd, const char* db_name);
void db_disconnect(MYSQL* mysql);
int db_operate(MYSQL* mysql, const char* statement);
MYSQL_RES* db_query(MYSQL * mysql, const char* statement);
char* db_result_to_cJson(MYSQL_RES * res);
int db_free_result(char* result);
int db_print_res(MYSQL_RES* res);

#endif // !_DB_BASE_H
