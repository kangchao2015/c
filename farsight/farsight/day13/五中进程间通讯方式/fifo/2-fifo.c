#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd;
	if(mkfifo("fifo", 0755) < 0){
		if(errno == EEXIST){
			fd = open("fifo", O_RDWR);
		}
		else{
			perror("fail to mkfifo");
			return -1;
		}
	}
			
	return 0;
}
