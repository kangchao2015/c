#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{

	pid_t  pid;
	pid_t  pid1;
	pid_t pid2;
	int status;

	if((pid = fork()) < 0)
	{
		perror("Failed to fork");
		return -1;
	}
	else if(pid == 0)  // child1
	{
		sleep(5);
		printf("In child1. child1 pid:%d  parent pid:%d \n", getpid(), getppid());
		exit(0);

	}
	else
	{
		printf("In parent. child1 pid:%d self pid:%d \n", pid, getpid());

		while(waitpid(-1, 0, WNOHANG) == 0)
		{
			sleep(1);
			printf("waitpid ...\n");
		}

		printf("After waitpid.\n");

		
	}

	
	return 0;
}
