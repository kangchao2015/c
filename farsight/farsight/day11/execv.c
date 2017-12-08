#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	char * arv[] = {" ", "-lh", NULL};

	printf("Before execl.\n");

	if(execvp("ls", arv) < 0)
	{
		perror("Failed to execl.\n");
		return -1;
	}

	printf("After execl.\n");

	return 0;
}
