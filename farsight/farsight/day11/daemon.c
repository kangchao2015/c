#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pid_t pid;
	int i = 0;

	if((pid = fork()) < 0)
	{
		perror("Failed to fork");
		return -1;
	}
	else if(pid > 0)
	{
		exit(0);
	}
	else
	{
		setsid();
		chdir("/");
		umask(0); // 0664 & ~umask
		
		for(i = 0; i < getdtablesize(); i++)
		{
			close(i);
		}

		while(1);
	}


	return 0;
}
