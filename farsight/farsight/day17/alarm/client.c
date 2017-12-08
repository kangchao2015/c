#include "head.h"

#define N 32

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr;
	socklen_t len = sizeof(serveraddr);
	char buf[N] = {0};
	//1、设定基于TCP通信的标准
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("fail to socket");
		return -1;
	}

	bzero(&serveraddr, len);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));//端口号
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);  //IP地址

	//2、绑定IP地址和端口号
	if(connect(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		perror("fail to connect");
		close(sockfd);
		return -1;
	}

	while(1)
	{
		fgets(buf, N, stdin);
		send(sockfd, buf, N, 0);
	}
	close(sockfd);
	return 0;
}
