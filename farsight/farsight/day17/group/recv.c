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
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]); //组播地址

	if(bind(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		perror("fail to bind");
		exit(1);
	}
	
	//将本机IP地址添加到组播地址中去
	struct ip_mreq mymreq;
	mymreq.imr_multiaddr.s_addr = inet_addr(argv[1]);
	mymreq.imr_interface.s_addr = inet_addr("192.168.1.222");
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mymreq, sizeof(struct ip_mreq));

	while(1)
	{
		recvfrom(sockfd, buf, N, 0, (struct sockaddr*)&serveraddr, &len);
		printf("--> %s \n", buf);
	}

	close(sockfd);
	return 0;
}
