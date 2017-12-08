//指针：指针变量、地址常量

#include <stdio.h>

int main(int argc, const char *argv[])
{
	int  a = 10;
	float b = 12.34;
	char c = 'D';

	int *p = &a; 					//p：指针变量，用于存放地址量的变量
	float *w = &b; 					//*：类型的一部分
	char *q = &c;

	printf("*p = %d\n",*p ); 		//*：指针解引用，获取地址里的内容
	printf("*w = %f\n",*w ); 	
	printf("*q = %c\n",*q ); 


	printf("p+0 = %p\n",p); 	
	printf("p+1 = %p\n",p+1); 	
	printf("p+2 = %p\n",p+2); 	
	printf("p+3 = %p\n",p+3); 	

	printf("size = %d\n",sizeof(p));
	printf("size = %d\n",sizeof(w));
	printf("size = %d\n",sizeof(q));

	
	return 0;
}
