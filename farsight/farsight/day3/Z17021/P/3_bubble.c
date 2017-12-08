//冒泡排序

#include <stdio.h>

#define N 5

int main(int argc, const char *argv[])
{
	int a[N] = {10,1,12,23,4};
	int i,j,temp;

	for(i=0; i<N-1; i++) 			//i：循环的轮数
	{
		for(j=0; j<N-i-1; j++) 		//j：循环比较前一个数的下标   j+1：后一个数的下标
		{
			if(a[j] < a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}

	for(i=0; i<N; i++)
	{
		printf("a[%d] = %d\n",i, a[i]);
	}


	
	return 0;
}
