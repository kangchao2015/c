#include <stdio.h> 		//printf

void fun();

void fun()
{
	printf("hello \n");
}

int main(int argc, const char *argv[])
{
	printf("fun begin\n");
	fun();
	printf("fun end\n");

//	printf("fun = %p\n",fun); 			//函数名：函数的入口地址
	
	return 0;
}



