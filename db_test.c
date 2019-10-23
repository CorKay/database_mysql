#include "db_base.h"

//Test
int main()
{
	test_info example = { 30,"XiaoHong" };
	test_info new_example = { 30,"LaoHong" };

	MYSQL_RES** test_ret;

	
	test_table_insert(&example);						//插入
	if (test_table_select(test_ret) == 0)					//查询
	{
		printf("Select1 test successful \n");
		print_res(*test_ret);						//测试返回内容
		db_free_select_result(test_ret);
	}
	
	test_table_update(&new_example);					//更新
	if (test_table_select(test_ret) == 0)					//查询
	{
		printf("Select2 test successful \n");
		print_res(*test_ret);
		db_free_select_result(test_ret);
	}
	
	test_table_delete(&new_example);					//删除
	if (test_table_select(test_ret) == 0)					//查询
	{
		printf("Select3 test successful \n");
		print_res(*test_ret);
		db_free_select_result(test_ret);
	}
	
	return 0;
}
