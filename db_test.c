#include "db_base.h"

//Test
int main()
{
	test_info example = { 30,"XiaoHong" };
	test_info new_example = { 30,"LaoHong" };

	MYSQL_RES** test_ret;

	
	if (test_table_insert(&example) == 0)				//插入
	{
		printf("Insert test successful \n");
	}
	if (test_table_select(test_ret) == 0)				//查询
	{
		printf("Select1 test successful \n");
		print_res(*test_ret);							//测试返回内容
		db_free_select_result(test_ret);
	}
	
	if (test_table_update(&new_example) == 0)			//更新
	{
		printf("Update test successful \n");
	}
	if (test_table_select(test_ret) == 0)				//查询
	{
		printf("Select2 test successful \n");
		print_res(*test_ret);
		db_free_select_result(test_ret);
	}
	
	if (test_table_delete(&new_example) == 0)			//删除
	{
		printf("Delete test successful \n");
	}
	if (test_table_select(test_ret) == 0)				//查询
	{
		printf("Select3 test successful \n");
		print_res(*test_ret);
		db_free_select_result(test_ret);
	}
	
	return 0;
}
