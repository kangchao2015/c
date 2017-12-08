//TCP服务器的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> //inet_addr,htons
#include <stdlib.h> //exit
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h> //select

#define N 128
#define errlog(errmsg) do{perror(errmsg);\
						  printf("%s --> %s --> %d\n", __FILE__, __func__, __LINE__);\
				          exit(1);\
						  }while(0)

int main(int argc, const char *argv[]) //./a.out 192.168.1.118 9999
{
	int sockfd, acceptfd;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};

	fd_set readfds;
	int maxfd;
	int i = 0;
	fd_set tempfds;
	
	if(argc < 3)
	{
		printf("you must input 3 arguments\n");
		exit(1);
	}

	//第一步：创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	printf("sockfd = %d\n", sockfd);

	//第二步：填充服务器网络信息结构体
	//inet_addr：将点分十进制IP地址转化为网络识别的
	//htohs：将主机字节序转化为网络字节序
	//atoi：将数字型字符串转化为整型数据
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	//第三步：将套接字域网络信息结构体绑定
	if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		errlog("fail to bind");
	}

	//第三步：将套接字设置为监听状态
	if(listen(sockfd, 5) < 0)
	{
		errlog("fail to listen");
	}

	//使用select函数实现tcp并发服务器

	//第一步：清空集合
	FD_ZERO(&readfds);

	maxfd = sockfd;

	//第二步：将需要的文件描述符添加到集合里面
	FD_SET(sockfd, &readfds);

	while(1)
	{
		tempfds = readfds;

		//第三步：调用select函数阻塞等待文件描述符准备就绪
		if(select(maxfd + 1, &tempfds, NULL, NULL, NULL) < 0)
		{
			errlog("fail to select");
		}
		
		//第四步：判断文件描述符
		for(i = 0; i < maxfd + 1; i++)
		{
			if(FD_ISSET(i, &tempfds))
			{
				if(i == sockfd)
				{
					if((acceptfd = accept(i, (struct sockaddr *)&clientaddr, &addrlen)) < 0)
					{
						errlog("fail to accept");
					}

					printf("%s ---> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

					printf("acceptfd = %d\n", acceptfd);

					FD_SET(acceptfd, &readfds);

					maxfd = maxfd > acceptfd ? maxfd : acceptfd;
				}
				else
				{
					if(recv(i, buf, N, 0) <= 0)
					{
						errlog("fail to recv");
					}

					if(strncmp(buf, "quit", 4) == 0)
					{
						FD_CLR(i, &readfds);
						close(i);
						break;
					}
					else
					{
						printf("client >>> %s\n", buf);

						strcat(buf, " *_*");

						if(send(i, buf, N, 0) < 0)
						{
							errlog("fail to send");
						}
					}
				}
			}
		}
	}

	return 0;
}
