#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a = 10;
	char b = 'S';

	void *p = &a; 	//泛型指针
	printf("*p = %d\n",*(int *)p);

	p = &b;
	printf("*p = %c\n",*(char *)p);

	return 0;
}
