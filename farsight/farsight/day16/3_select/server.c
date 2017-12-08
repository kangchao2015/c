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

	//使用select函数实现IO多路复用
	//同步IO操作，允许一个程序可以操作多个文件描述符，阻塞等待
	//有文件描述符准备就绪，如果有文件描述符准备就绪，则函数立
	//即返回，并执行相应的IO操作

	//注意：当文件描述符准备就绪，会清空除这个文件描述符以外其他所有的文件描述符，所以需要每次都添加

	//第一步：清空集合
	FD_ZERO(&readfds);

	maxfd = sockfd;

	while(1)
	{
		//第二步：将需要的文件描述符添加到集合里面
		FD_SET(0, &readfds);
		FD_SET(sockfd, &readfds);

		//第三步：调用select函数阻塞等待文件描述符准备就绪
		if(select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0)
		{
			errlog("fail to select");
		}
		
		//第四步：判断文件描述符
		for(i = 0; i < maxfd + 1; i++)
		{
			if(FD_ISSET(i, &readfds))
			{
				if(i == 0)
				{
					fgets(buf, N, stdin);
					printf(">>>%s\n", buf);
				}
				else
				{
					//第四步：阻塞等待客户端的连接请求
					if((acceptfd = accept(i, (struct sockaddr *)&clientaddr, &addrlen)) < 0)
					{
						errlog("fail to accept");
					}

					printf("%s ---> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				}
			}
		}
	}

	return 0;
}
