//指针函数：返回值是指针的函数 			 int *fun(int a,int b);
//函数指针：本质是指针，用来指向函数的入口地址(函数名)

#include <stdio.h>

int add(int a, int b)
{
	printf("add = %d\n",a+b);
	return 0;
}

int sub(int a, int b)
{
	printf("sub = %d\n",a-b);
	return 0;
}

int main(int argc, const char *argv[])
{
	int (*p)(int a,int b) = add; 		//p ：变量  <==> add：常量
	p = sub;
	p(12,13);
//	add(12,34);

	return 0;
}
