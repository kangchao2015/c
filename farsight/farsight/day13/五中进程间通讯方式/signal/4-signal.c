#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

pid_t pid;
void driver_handler(int signum){
	if(signum == SIGUSR1){
		puts("driver: let's go");
	}
	else if(signum == SIGUSR2){
		puts("driver: stop the bus");
	}
	else if(signum == SIGTSTP){
		kill(getppid(), SIGUSR1);
	}
}
void soler_handler(int signum){
	if(signum == SIGINT){
		kill(pid, SIGUSR1);
	}
	else if(signum == SIGQUIT){
		kill(pid, SIGUSR2);
	}
	else if(signum == SIGUSR1){
		puts("soler: please get off the bus");
	}
}
int main(int argc, char *argv[])
{
	pid = fork();
	if(pid < 0){
		perror("fail to fork");
		return -1;
	}
	else if(pid == 0){
		//driver
		signal(SIGUSR1, driver_handler);
		signal(SIGUSR2, driver_handler);
		signal(SIGTSTP, driver_handler);

		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		while(1)
			;
	}
	else{
		//soler	
		signal(SIGINT, soler_handler);
		signal(SIGQUIT, soler_handler);
		signal(SIGUSR1, soler_handler);

		signal(SIGTSTP, SIG_IGN);
		while(1)
			;
	}
	return 0;
}
