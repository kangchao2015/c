#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if(mkfifo("fifo", 0755) < 0){
		perror("fail to mkfifo");
		return -1;
	}

	int fd;

	if((fd = open("fifo", O_RDWR)) > 0){
		printf("fd = %d\n", fd);
	}		
	return 0;
}
