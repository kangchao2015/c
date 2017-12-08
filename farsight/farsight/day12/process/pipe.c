#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int fd[2];

	if(pipe(fd) < 0)
	{
		perror("fail to pipe");
		exit(1);
	}

	//创建父子进程，让子进程获取父进程的文件描述符，来操作同一个管道
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fail to fork");
		exit(1);
	}

	if(pid == 0) //子进程
	{
		char buf[32] = {0};
		while(1)
		{
			read(fd[0], buf, 32);
			if(strncmp(buf, "quit", 4) == 0)
			{
				break;
			}
			printf("--> %s \n", buf);
		}
	}
	else
	{
		char buf[32] = {0};
		//父进程从终端读取数据，往管道中写数据
		while(1)
		{
			fgets(buf, 32, stdin);
			write(fd[1], buf, 32);
			if(strncmp(buf, "quit", 4) == 0)
			{
				wait(NULL);
				break;
			}

		}
	}
	return 0;
}
