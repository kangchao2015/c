#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int fd;
	int buf[4] = {1,2,3,4};
	ssize_t bytes;

	fd = open("test",O_WRONLY | O_CREAT | O_EXCL,0666);
	if(fd < 0)
	{
		if(errno == EEXIST)
		{
			fd = open("test",O_WRONLY | O_TRUNC);
		}
		else
		{
			perror("fail to open");
			return -1;
		}
	}

	bytes = write(fd,buf,16);
	printf("bytes = %d\n",bytes);
	close(fd);
	return 0;
}
