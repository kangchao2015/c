//指针数组：本质是数组，元素是指针类型

#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a = 10;
	int b = 20;
	int c[5] = {0,1,2,3,4};

//  int a[5];
	int *p[3]; 				//指针数组
	p[0] = &a;
	p[1] = &b;
	p[2] = &c[1];

	printf("*p[0]    = %d\n",*p[0]);
	printf("*p[1]    = %d\n",*p[1]);
	printf("*(p[2]+2)= %d\n",*(p[2]+2));

//	printf("*(p[2][2]= %d\n",p[2][2]);




	return 0;
}
