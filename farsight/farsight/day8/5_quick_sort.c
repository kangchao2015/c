#include <stdio.h>

#define N 7

int quick_short(int *a, int i, int j)
{
	int low = i;
	int high = j;		
	int x = a[i]; 		//基准值：将第一个数作为基准值

	while(i<j)  
	{
		while(i<j && x <= a[j])
		{
			j--;
		}
		a[i] = a[j]; 					
		

		while(i<j && x >= a[i])
		{
			i++;
		}
		a[j] = a[i];
	}

	a[i] = x;
	
	if(low < i-1)
	{
		quick_short(a,low, i-1);
	}

	if(i+1 < high)
	{
		quick_short(a,i+1, high);
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	int i;
	int a[N] = {0,11,2,13,4,15,0};
	quick_short(a,0,N-1);

	for(i=0; i<N; i++)
	{
		printf("%d ",a[i]);
	}
	putchar(10);


	return 0;
}
