#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	
	printf("Before execl.\n");

	if(execl("./a.out", " ", NULL) < 0)
	{
		perror("Failed to execl.\n");
		return -1;
	}

	printf("After execl.\n");

	return 0;
}
