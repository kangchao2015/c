#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define N 128

int main(int argc, const char *argv[])
{
	int sockfd, acceptfd;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t len = sizeof(serveraddr);
	char buf[N] = {0};
	//create sockets
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("fail to socket");
		exit(1);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2])); //port
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	//bind address
	if(connect(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		perror("fail to bind");
		exit(1);
	}
	
	while(1)
	{
		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';
		send(sockfd, buf, N, 0);
	}
	return 0;
}
