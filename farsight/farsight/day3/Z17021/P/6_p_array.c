//指针：指针变量， 地址常量

#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[5] = {0,1,2,3,4};
	int i;

	for(i=0; i<5; i++)
	{
		printf("%p  ",&a[i]);
	}
	putchar(10);

	printf("a+0 = %p\n",a); 		//a：首地址
	printf("a+1 = %p\n",a+1); 
	printf("a+2 = %p\n",a+2); 
	printf("a+3 = %p\n",a+3); 

	printf("a+0 = %d\n",*(a+0)); 	//a：首地址
	printf("a+1 = %d\n",*(a+1));  	//a[i]  <==>  *(a+i)
	printf("a+2 = %d\n",*(a+2));  	//a[i]：指针加单位长度后，取内容运算
	printf("a+3 = %d\n",*(a+3)); 

	printf("a[0] = %d\n",a[0]); 

	return 0;
}
