#include "db_base.h"

//Test
int main()
{
	test_info example = { 30,"XiaoHong" };
	test_info new_example = { 30,"LaoHong" };

	query_test_info query_example;
	query_test_info* test_example = &query_example;

	
	test_table_insert(&example);						//插入
	test_table_select(test_example);					//查询
	if (&query_example.testInfo != NULL)
	{
		printf("Select1 Return successful,num_rows : %d \n",query_example.num_rows);
		query_example.cur_row = 0;
	}
	else
	{
		printf("Select1 Return failed \n");
		query_example.cur_row = 0;
	}
	
	test_table_update(&new_example);					//更新	
	test_table_select(test_example);					//查询
	if (&query_example.testInfo != NULL)
	{
		printf("Select2 Return successful,num_rows : %d \n", query_example.num_rows);
		query_example.cur_row = 0;
	}
	else
	{
		printf("Select2 Return failed \n");
		query_example.cur_row = 0;
	}
	
	test_table_delete(&example);						//删除
	test_table_select(test_example);					//查询
	if (&query_example.testInfo != NULL)
	{
		printf("Select3 Return successful,num_rows : %d \n", query_example.num_rows);
		query_example.cur_row = 0;
	}
	else
	{
		printf("Select3 Return failed \n");
		query_example.cur_row = 0;
	}
	
	return 0;
}
