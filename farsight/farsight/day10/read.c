#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int fd;
	int buf[6] = {0},i;
	ssize_t bytes;

	fd = open("test",O_RDONLY);
	if(fd < 0)
	{
		perror("fail to open");
		return -1;
	}

	bytes = read(fd,buf,24);
	printf("bytes = %d\n",bytes);
	for(i = 0;i < 4;i++)
	{
		printf("buf[%d] = %d\n",i,buf[i]);
	}
	close(fd);
	return 0;
}
