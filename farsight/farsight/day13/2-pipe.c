#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define N 128
int main(int argc, char *argv[])
{
	int fd[2];
	char wbuf[N] = "";
	char rbuf[N] = "";
	if(pipe(fd) < 0){
		perror("fail to pipe");
		return -1;
	}

	pid_t pid;

	pid = fork();

	if(pid < 0){
		perror("fail to fork");
		return -1;
	}
	else if(pid == 0){
		while(1){
			fgets(wbuf, N, stdin);
			wbuf[strlen(wbuf) - 1] = '\0';

			write(fd[1], wbuf, strlen(wbuf));

			if(strncmp(wbuf, "quit", 4) == 0){
				break;
			}
		}
	}
	else{
		while(1){
			close(fd[1]);
			read(fd[0], rbuf, N);

			if(strncmp(rbuf, "quit", 4) == 0){
				break;
			}
			printf("rbuf = %s\n", rbuf);
		}
	}
	return 0;
}
