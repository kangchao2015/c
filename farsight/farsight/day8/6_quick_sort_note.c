#include <stdio.h>

#define N 7

int quick_short(int *a, int i, int j)
{
	int low = i;
	int high = j;		
	int x = a[i]; 		//基准值：将第一个数作为基准值

	while(i<j)
	{
		//若x < a[j]，j往前继续执行
		while(i<j && x <= a[j])
		{
			j--;
		}
		//跳出循环：若a[j]较小，放x前面；若i==j,a[i]=a[j]无影响;
		a[i] = a[j]; 					
		

		//若x > a[i]，i往后继续执行
		while(i<j && x >= a[i])
		{
			i++;
		}
		//跳出循环：若a[i]较大，放x后面；若i==j,a[i]=a[j]无影响;
		a[j] = a[i];
	}

	//跳出大循环：基准值x重新存储在中间部位
	a[i] = x;
	
	//基准值左边的所有数据再次进行快速查找（递归）
	if(low < i-1)
	{
		quick_short(a,low, i-1);
	}

	//基准值右边的所有数据再次进行快速查找（递归）
	if(i+1 < high)
	{
		quick_short(a,i+1, high);
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	int i;
	int a[N] = {0,11,2,13,4,15,6};
	quick_short(a,0,N-1);

	for(i=0; i<N; i++)
	{
		printf("%d ",a[i]);
	}
	putchar(10);


	return 0;
}
