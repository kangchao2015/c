#include "head.h"

#define N 32

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

	fd_set readfds, tempfds;  //读描述符集合
	FD_ZERO(&readfds);  //清空读描述符集合
	int maxfd;  //代表最大描述符
	maxfd = sockfd;
	int i = 0;  //用来循环

	struct timeval tv;

	int time_out;  //变量接收超时的返回值

	while(1)
	{
		//每检查一次，时间需要重新设置	
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		//sockfd \ acceptfd 这两个描述符,把这两个描述符添加到集合中
		FD_SET(sockfd, &readfds);
		tempfds = readfds;//定义临时变量
		//通过select检测描述符是否满足条件，满足条件的留在描述父集合中，不满足，从集合中清除掉
		if((time_out = select(maxfd+1, &tempfds, NULL, NULL, &tv)) < 0)
		{
			perror("fail to select");
			return -1;
		}
		else if(time_out == 0)
		{
			printf("connect or send/recv ...\n");
		}
		//检查哪一个描述符准备就绪
		else
		{
			for(i = 0; i < maxfd+1; i++)
			{
				if(FD_ISSET(i, &tempfds))//注意tempfds，看这个集合中那些描述符是有效的
				{
					if(i == sockfd)
					{
						acceptfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
						if(acceptfd < 0)
						{
							perror("fail to accept");
							close(acceptfd);
							return -1;
						}
						//打印客户端IP地址和端口号
						printf("  addr = %s, port = %d \n ", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
						FD_SET(acceptfd, &readfds);//把acceptfd添加到描述父集合中，跟对应的客户端实现通信
						maxfd = acceptfd;
					}
					else// 注意因为有多个客户端链接操作，而使用了同一个变量acceptfd
					{
						recv(i, buf, N, 0);
						printf("--> %s \n", buf);
					}
				}
			}
		}

	}
	close(sockfd);
	close(acceptfd);
	return 0;
}
