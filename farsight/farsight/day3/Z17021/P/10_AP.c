//数组指针：本质是指针，专用于指向数组的指针(多数用于指向二维数组)

#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[3][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11}};

	//int *p[3]; 						//指针数组
	int (*p)[4] = a; 					//数组指针：[4]必须指向列数为4的数组 
	printf("%d\n",p[1][2]); 		  	//p <==> a
	printf("%d\n",*(p[1]+2));
	printf("%d\n",*(*(p+1)+2));




	
	return 0;
}
