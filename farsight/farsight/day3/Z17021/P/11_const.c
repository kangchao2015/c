#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a = 10;
	const int *p = &a; 		//*p 是只读的数据
//	*p = 100;
	printf("*p = %d\n",*p);


	int x = 20;
	int y = 30;
	int * const w = &x; 	//w 是只读的数据
//	w = &y;
	printf("x = %d\n",x);


	return 0;
}
