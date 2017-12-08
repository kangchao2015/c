#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, const char *argv[])
{
	int fd;

	fd = open("test",O_RDWR | O_CREAT | O_EXCL,0777);
	if(fd < 0)
	{
		if(errno == EEXIST)
		{
			if((fd = open("test",O_RDWR | O_TRUNC)) < 0)
			{
				perror("fail to open");
				return -1;
			}
		}
		else
		{
			perror("fail to open");
			return -1;
		}
	}

	close(fd);
	return 0;
}
