#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{

	pid_t  pid;
	int m = 10;

	//printf("Hello world.\n");
	printf("Hello world.");

	if((pid = fork()) < 0)
	{
		perror("Failed to fork");
	}
	else if(pid == 0)
	{
		printf("In child. child pid:%d  parent pid:%d \n", getpid(), getppid());
		printf("child m:%d --> %p\n", m, &m);
		m = 20;
		printf("child m:%d --> %p\n", m, &m);
	}
	else
	{
		sleep(3);
		printf("In parent. child pid:%d self pid:%d \n", pid, getpid());
		printf("child m:%d --> %p \n", m, &m);
	}

	
	return 0;
}
