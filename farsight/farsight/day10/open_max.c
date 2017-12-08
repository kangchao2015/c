#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	int fd;

	close(0);
	close(2);
	while(1)
	{
		fd = open("test",O_RDONLY);
		if(fd < 0)
		{
			break;
		}
		else
		{
			printf("fd = %d\n",fd);
		}
	}
	return 0;
}
