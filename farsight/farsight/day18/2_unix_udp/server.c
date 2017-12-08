//UDP服务器的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <sys/un.h>
#include <arpa/inet.h> //inet_addr,htons
#include <stdlib.h> //exit
#include <string.h>

#define N 128
#define errlog(errmsg) do{perror(errmsg);\
						  printf("%s --> %s --> %d\n", __FILE__, __func__, __LINE__);\
				          exit(1);\
						  }while(0)

int main(int argc, const char *argv[]) //./a.out 192.168.1.118 9999
{
	int sockfd;
	struct sockaddr_un serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};

	//第一步：创建套接字
	if((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第二步：填充服务器本地信息结构体
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path, "server_socket");
	
	//第三步：将套接字域网络信息结构体绑定
	if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		errlog("fail to bind");
	}

	
	while(1)
	{
		if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&clientaddr, &addrlen) <= 0)
		//if(recvfrom(sockfd, buf, N, 0, NULL, NULL) <= 0)
		{
			errlog("fail to recvfrom");
		}
		
		if(strncmp(buf, "quit", 4) == 0)
		{
			break;
		}
		else
		{
			printf("client >>> %s\n", buf);

			strcat(buf, " *_*");

			if(sendto(sockfd, buf, N, 0, (struct sockaddr *)&clientaddr, addrlen) < 0)
			{
				errlog("fail to sendto");
			}

		}
	}

	return 0;
}
