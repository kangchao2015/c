#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	
	printf("Before exit!");

//	_exit(0);
	exit(0);

	printf("After exit!\n");


	return 0;
}
