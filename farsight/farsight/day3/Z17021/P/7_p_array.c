#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[5] = {10,11,2,3,4};
	int *p = a; 						// p = &a[0];

	printf("a[2]   = %d\n",a[2]);
	printf("*(a+2) = %d\n",*(a+2)); 	//a：常量   p：变量
	printf("*(p+2) = %d\n",*(p+2));
	printf("p[2]   = %d\n",p[2]);

	printf("a[2]   = %p\n",&a[2]);
	printf("*(a+2) = %p\n",&*(a+2));
	printf("*(p+2) = %p\n",&*(p+2));
	printf("p[2]   = %p\n",&p[2]);
	printf("*(a+2) = %p\n",a+2); 
	printf("*(p+2) = %p\n",p+2); 		//&与*互为逆运算

	return 0;
}
