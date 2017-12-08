#include "head.h"

#define N 32

void handler(int signo)
{
	
}

int main(int argc, const char *argv[])
{
	int sockfd, acceptfd;
	struct sockaddr_in serveraddr, clientaddr;
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
	if(bind(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		perror("fail to bind");
		close(sockfd);
		return -1;
	}

	//3、设置监听描述符的个数
	if(listen(sockfd, 5) < 0)
	{
		perror("fail to listen");
		close(sockfd);
		return -1;
	}

//	signal(SIGALRM, handler);

	//读
	sigaction(SIGALRM, NULL, NULL);
	//改
	struct sigaction mysig;
	mysig.sa_handler = handler;
	mysig.sa_flags &= ~SA_RESTART;
	//写
	sigaction(SIGALRM, &mysig, NULL);
	
	
	while(1)
	{
		alarm(5);
		acceptfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
		if(acceptfd < 0)
		{
			//	printf("errno = %d \n", errno);
			if(errno == 4)
			{
				printf("accept timeout ... \n");
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
				alarm(5);
				if(recv(acceptfd, buf, N, 0) < 0)
				{

					if(errno == 4)
					{
						printf("recv timeout ... \n");
					}
					else
					{
						perror("fail to recv");
						exit(1);
					}
				}
			}
		}
	}
	close(sockfd);
	return 0;
}
