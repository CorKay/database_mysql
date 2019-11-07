**db_base/底层操作(类似函数库,通用):**

* 数据库连接:`MYSQL* db_connect(MYSQL* mysql, const char* host, const char* user, const char*  passwd, const char* db_name)`
* 数据库断连:`void db_disconnect(MYSQL* mysql)`
* 数据库操作(执行增删改语句):`int db_operate(MYSQL* mysql, const char* statement)`
* 数据库查询(执行查询操作,返回MYSQL结果集):`MYSQL_RES* db_query(MYSQL * mysql, const char* statement)`
* 结果转换函数(将MYSQL_RESULT格式的结果集转为cJSON_Array格式字符串):`char* db_result_to_cJson(MYSQL_RES * res)`
* 释放函数(提供给使用者释放结果集内存):`int db_free_result(char* result)`
* 打印函数(在调试中使用的打印结果集的函数):`int db_print_res(MYSQL_RES* res)`

    
**db_implement/封装的中间层调用,提供给业务层使用:**

* 插入接口(调用底层接口完成连接、插入语句的执行、链接断开操作,返回数据表变化的行数):`int implement_insert(const char* statement)`
* 删除接口(调用底层接口完成连接、删除语句的执行、链接断开操作,返回数据表变化的行数):`int implement_delete(const char* statement)`
* 修改接口(调用底层接口完成连接、修改语句的执行、链接断开操作,返回数据表变化的行数):`int implement_update(const char* statement)`
* 查询接口(调用底层接口完成连接、查询语句的执行、MYSQL结果集到cJSON字符串的转换、结果集释放、链接断开操作,返回cJSON_Array格式字符串):`char* implement_select(const char* statement)`

**db_business/业务层代码,根据不同业务表写就,提供给使用者调用:**
* 目前的想法是根据不同业务表实际的需求在这一层完成相应sql语句的拼接,然后调用上一层封装好的接口执行操作,以下为测试程序的函数原型(这里为了方便传值,依然使用了结构体的形式为想要操作的字段赋值)
       
```
        *int test_table_insert(test_info* test);
        
        *int test_table_delete(test_info* test);
        
        *int test_table_update(test_info* test);
//此处select因为执行的是"select *"的操作,所以没有传参数         
        *char* test_table_select();  
```


