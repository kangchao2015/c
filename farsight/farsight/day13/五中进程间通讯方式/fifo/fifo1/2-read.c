#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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
		fd = open("fifo", O_RDONLY);
		printf("fd = %d\n", fd);
	}
	puts("start read...");

	while(1){
		read(fd, buf, N);

		if(strncmp(buf, "quit", 4) == 0){
			break;
		}

		printf("buf = %s\n", buf);
	}
	return 0;
}
