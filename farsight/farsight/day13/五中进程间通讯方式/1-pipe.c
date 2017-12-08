#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define N 1024
int main(int argc, char *argv[])
{
	int fd[2];
	char wbuf[N];
	char rbuf[N];
	int count = 0;
	if(pipe(fd) < 0){
		perror("failed to pipe");
		return -1;
	}

	while(1){
		write(fd[1], wbuf, N);
		count++;

		printf("count = %d\n", count);

		if(count == 64){
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
			read(fd[0], rbuf, N);
		}

	}
	return 0;
}
