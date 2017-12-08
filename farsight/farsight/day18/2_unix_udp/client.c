//UDP客户端的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <sys/un.h> //sockaddr_un
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
	int sockfd, acceptfd;
	struct sockaddr_un serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr);
	char buf[N] = {};


	//第一步：创建套接字
	if((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第二步：填充服务器本地信息结构体
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path, "server_socket");

	//第三步：填充客户端本地信息结构体
	clientaddr.sun_family = AF_UNIX;
	strcpy(clientaddr.sun_path, "client_socket");

	//第四步：将套接字域客户端本地信息结构体进行绑定
	if(bind(sockfd, (struct sockaddr *)&clientaddr, addrlen) < 0)
	{
		errlog("fail to bind");
	}

	while(1)
	{
		//通信
		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';
			
		if(sendto(sockfd, buf, N, 0, (struct sockaddr *)&serveraddr, addrlen) < 0)
		{
			errlog("fail to sendto");
		}

	
		if(strncmp(buf, "quit", 4) == 0)
		{
			break;
		}
		else 
		{
			//if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&serveraddr, &addrlen) <= 0)			
			if(recvfrom(sockfd, buf, N, 0, NULL, NULL) <= 0)
			{
				errlog("fail to recvfrom");
			}

			printf("server >>> %s\n", buf);
		}
	}

	return 0;
}
