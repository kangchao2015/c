#include <stdio.h>

int fun(int a)
{
	if(a > 0)
	{
		printf("***********\n");
		a--;
		fun(a);
	}

	printf("------------\n");

	return 0;
}

int main(int argc, const char *argv[])
{
	fun(2);

	
	return 0;
}
