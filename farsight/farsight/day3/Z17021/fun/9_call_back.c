#include <stdio.h>

int add(int a, int b)
{
	printf("add = %d\n",a+b);
	return 0;
}

//函数指针：传递函数名时，使用函数指针承接
int call_back( int(*p)(int a,int b), int x, int y)  			//库函数，系统调用函数
{
	p(x,y); 		// add(x,y);
	return 0;
}

int main(int argc, const char *argv[])
{
	call_back(add,10,5);
	
	return 0;
}
