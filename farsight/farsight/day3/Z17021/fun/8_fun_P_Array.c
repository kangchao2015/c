//指针函数：返回值是指针的函数 			 int *fun(int a,int b);
//函数指针：本质是指针，用来指向函数的入口地址(函数名)
//函数指针数组：本质是数组，元素是函数指针类型

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
//	int (*p)(int a,int b) = add; 		//p ：变量  <==> add：常量
	int (*p[2])(int a,int b); 	 		//函数指针数组
	p[0] = add;
	p[1] = sub;

	p[1](10,20);

	return 0;
}
