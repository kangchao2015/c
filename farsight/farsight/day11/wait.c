#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{

	pid_t  pid;

	if((pid = fork()) < 0)
	{
		perror("Failed to fork");
	}
	else if(pid == 0)
	{
		sleep(5);
		printf("In child. child pid:%d  parent pid:%d \n", getpid(), getppid());
	}
	else
	{
		wait(NULL);
		printf("In parent. child pid:%d self pid:%d \n", pid, getpid());
	
		while(1);
	}

	
	return 0;
}
