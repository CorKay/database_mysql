# database_mysql
根据项目需要写的一套C操作MySQL的接口,只涉及底层增删改查,不涉及业务层,
水平有限,代码仅供初学者参考.

# master request
增删改 查 打印查询结果

# select_calback_version
增删改 查 根据不同的业务表创建结构体,将查询结果传给对应表的结构体  只能返回最后一条查询结果

# return_mysql_result_version
通用接口  一个mysql_res类型的双指针用做返回
