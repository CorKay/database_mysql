#include "db_base.h"
#include "db_business.h"

//Test
int main()
{
	test_info example = { 30,"XiaoHong" };
	test_info new_example = { 30,"LaoHong" };

	char* result_test1 = NULL;
	char* result_test2 = NULL;
	char* result_test3 = NULL;
	
	test_table_insert(&example);							//插入
	result_test1 = test_table_select();						//查询
	printf("select1 结果集: \n%s\n", result_test1);
	business_free(result_test1);
	

	test_table_update(&new_example);						//更新
	result_test2 = test_table_select();						//查询
	printf("select2 结果集: \n%s\n", result_test2);
	business_free(result_test2);
	
	
	test_table_delete(&new_example);						//删除
	result_test3 = test_table_select();						//查询
	printf("select3 结果集: \n%s\n", result_test3);
	business_free(result_test3);
	
	return 0;
}