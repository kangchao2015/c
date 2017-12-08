#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int fd_r,fd_w;
	char buf[32] = {0};
	ssize_t bytes;

	if((fd_r = open(argv[1],O_RDONLY)) < 0)
	{
		perror("fail to open fd_r");
		return -1;
	}

	if((fd_w = open(argv[2],O_WRONLY | O_CREAT | O_EXCL,0666)) < 0)
	{
		if(errno == EEXIST)
		{
			fd_w = open(argv[2],O_WRONLY | O_TRUNC);
		}
		else
		{
			close(fd_r);
			perror("fail to open fd_w");
			return -1;
		}
	}
	
	while(1)
	{
		bytes = read(fd_r,buf,sizeof(buf));
		if(bytes <= 0)
			break;
		else
			write(fd_w,buf,bytes);
	}

	close(fd_r);
	close(fd_w);
	return 0;
}
