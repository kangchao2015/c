#include <stdio.h>

int fun_1(int a)
{
	a += 5; 				//局部变量：生命期与函数同步
	printf("a = %d\n",a);
	return 0; 				//0：正常退出  -1：异常退场
}

int fun_2(int *b)
{
	*b += 5;
	printf("*b = %d\n",*b);
	return 0; 		
}

int main(int argc, const char *argv[])
{
	int x = 0;
	fun_1(x); 				//复制型传参
	fun_1(x);
	fun_1(x);
	printf("x = %d\n",x);

	int y = 0;
	fun_2(&y); 				//地址传递
	fun_2(&y);
	fun_2(&y);
	printf("y  = %d\n",y);

	return 0;
}
