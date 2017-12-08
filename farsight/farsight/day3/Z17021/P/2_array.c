//数组：元素类型相同，开辟空间连续，数组名是首元素地址

#include <stdio.h>

int main(int argc, const char *argv[])
{
	//类型 名字[元素个数]
	//下标：0 ~ N-1
	int a[5] = {0,1,2,3,4};
	int i;

	for(i=0; i<5; i++)
	{
		printf("%p\n",&a[i]);
	}

	printf("a = %p\n",a);  				//a：数组名


	return 0;
}
