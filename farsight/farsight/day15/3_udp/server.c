//UDP服务器的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <netinet/in.h> //sockaddr_in
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
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};
	
	if(argc < 3)
	{
		printf("you must input 3 arguments\n");
		exit(1);
	}

	//第一步：创建套接字
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
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

	
	while(1)
	{
		if(recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&clientaddr, &addrlen) <= 0)
		//if(recvfrom(sockfd, buf, N, 0, NULL, NULL) <= 0)
		{
			errlog("fail to recvfrom");
		}
		
		printf("%s ---> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

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
