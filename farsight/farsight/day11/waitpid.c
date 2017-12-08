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
		printf("In child1. child1 pid:%d  parent pid:%d \n", getpid(), getppid());

	}
	else
	{
		printf("In parent. child1 pid:%d self pid:%d \n", pid, getpid());

		if((pid1 = fork()) < 0)
		{
			perror("Failed to fork1");
			return -1;
		}
		else if(pid1 == 0) // child2
		{
			sleep(5);
			printf("In child2. child2 pid:%d  parent pid:%d \n", getpid(), getppid());

		}
		else  // grandpa
		{

			printf("Before waitpid.\n");
			waitpid(pid1, NULL, 0);
			printf("After waitpid.\n");
			while(1);

		}

	}

	
	return 0;
}
