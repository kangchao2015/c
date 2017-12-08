#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
	if(bind(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		perror("fail to bind");
		exit(1);
	}
	
	//listen
	listen(sockfd, 5);

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	socklen_t tv_len = sizeof(struct timeval);

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, tv_len);
	while(1)
	{
		
		acceptfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
		if(acceptfd < 0)
		{
		//	printf("errno = %d \n", errno);
			if(errno == 11)
			{
				printf("accept timeout ...\n");
			}
			else
			{
				perror("fail to accept");
				exit(1);
			}
		}
		else
		{
			while(1)
			{
				if(recv(acceptfd, buf, N, 0) < 0)
				{
					if(errno == 11)
					{
						printf("recv timeout ...\n");
					}
					else
					{
						perror("fail to recv");
						exit(1);
					}
				}
				else
				{
					printf("--> %s \n", buf);
				}
			}
		}
	}

	return 0;
}
