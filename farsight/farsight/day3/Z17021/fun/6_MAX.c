//数组指针

#include <stdio.h>

int find_MAX(int (*p)[4], int n, int m)
{
	int i,j,row = 0, line = 0;

	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			if(p[row][line] < p[i][j])
			{
				row = i;
				line = j;
			}
		}
	}
	printf("MAX=%d  row=%d  line=%d\n",p[row][line], row, line);

	return 0;

}

int main(int argc, const char *argv[])
{
	int a[3][4] = {{0,1,22,3},{4,15,6,7},{8,9,10,11}};
	find_MAX(a,3,4);

	return 0;
}
