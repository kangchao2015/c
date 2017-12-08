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
		while(1);
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
			printf("In child2. child2 pid:%d  parent pid:%d \n", getpid(), getppid());
			if((pid2 = fork()) < 0)
			{
				perror("Failed to fork2");
				return -1;
			}
			else if(pid2 == 0) // grandson
			{
				printf("In grandson. pid:%d  parent pid:%d \n", getpid(), getppid());
				exit(0);
			}
			else
			{
				wait(&status);
				printf("child2 --> status:%#x\n", status);
				exit(1);
			}

		}
		else  // grandpa
		{

			int ret;
			printf("Before wait.\n");
			ret = wait(&status);
			printf("Grandpa --> ret:%d, status:%#x %d\n", ret, status, status);

		}

	}

	
	return 0;
}
