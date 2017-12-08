#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handler(int signum){
	if(signum == SIGINT){
		puts("catch the SIGINT");
	}
}

int main(int argc, char *argv[])
{
	printf("pid = %d\n", getpid());
	if(signal(SIGINT, handler) == SIG_ERR){
		perror("fail to signal");
		return -1;
	}
	if(signal(SIGTSTP, SIG_IGN) == SIG_ERR){
		perror("fail to signal");
		return -1;
	}

	while(1)
		;
	return 0;
}
