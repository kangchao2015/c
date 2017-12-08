#include "head.h"

#define N 32 

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr;
	char buf[N]  ={0};
	socklen_t len = sizeof(struct sockaddr_in);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("fail to sockfd");
		exit(1);
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));//端口号
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);  //发送到组播地址中
	
	while(1)
	{
		fgets(buf, N, stdin);
		buf[strlen(buf)-1] = '\0';

		sendto(sockfd, buf, N, 0, (struct sockaddr*)&serveraddr, len);
	}
	close(sockfd);
	return 0;
}
