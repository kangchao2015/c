#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define N 128
int main(int argc, char *argv[])
{
	int fd;
	char buf[N] = "";
	if(mkfifo("fifo", 0755) < 0){
		if(errno == EEXIST){
			fd = open("fifo", O_RDWR);
			printf("fd = %d\n", fd);
		}
		else{
			perror("fail to mkfifo");
			return -1;
		}
	}
	else{
		fd = open("fifo", O_RDWR);
		printf("fd = %d\n", fd);
	}
	puts("start write...");

	while(1){
		fgets(buf, N, stdin);

		buf[strlen(buf) - 1] = '\0';

		write(fd, buf, strlen(buf));

		if(strncmp(buf, "quit", 4) == 0){
			break;
		}
	}
	return 0;
}
