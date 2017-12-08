#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[3][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11}};

	printf("a[1][2]     = %d\n",a[1][2]);
	printf("*(a[1]+2)   = %d\n",*(a[1]+2));
	printf("*(*(a+1)+2) = %d\n",*(*(a+1)+2));

	printf("a    = %p\n",a);
	printf("a[0] = %p\n",a[0]);


	//a：行指针，加1 移动1行
	//a[0]：列指针，加1 移动一列
	
	return 0;
}
