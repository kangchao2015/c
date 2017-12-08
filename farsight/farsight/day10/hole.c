#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	off_t off;
	int fd;
	char ch = '\0';

	fd = open("test",O_RDWR);
	if(fd < 0)
	{
		perror("fail to open");
		return -1;
	}

	off = lseek(fd,10,SEEK_END);
	printf("off = %ld\n",off);

	write(fd,&ch,1);

	off = lseek(fd,0,SEEK_END);
	printf("off = %ld\n",off);
	close(fd);
	return 0;
}
