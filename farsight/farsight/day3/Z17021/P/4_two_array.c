#include <stdio.h>

int main(int argc, const char *argv[])
{
	//0 ~ N-1
	//遍历：不重复的访问每一个元素
	
	int a[3][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11}};
	int i,j;

	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("%p  ",&a[i][j]);
		}
		putchar('\n'); 
	}

	printf("a    = %p\n",a); 				//以二维数组整体作为单位，的首地址
	printf("a+1  = %p\n",a+1); 				//行指针：加1移动一行
	printf("a+2  = %p\n",a+2);

	printf("a[0]+0 = %p\n",a[0]); 			//以一行作为单位，的首地址
	printf("a[0]+1 = %p\n",a[0]+1);  		//列指针：加1移动一列
	printf("a[0]+2 = %p\n",a[0]+2); 	


//	printf("a[1] = %p\n",a[1]);
//	printf("a[2] = %p\n",a[2]);

	return 0;
}
