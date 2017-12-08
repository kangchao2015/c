//TCP客户端的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <netinet/in.h> //sockaddr_in
#include <sys/un.h>
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
	struct sockaddr_un serveraddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};

	//第一步：创建套接字
	if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第二步：填充服务器本地信息结构体
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path, "server_socket");
	
	//第三步：发送客户端的连接请求
	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
	{
		errlog("fail to accept");
	}
	
	while(1)
	{
		//通信
		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';
		
		if(send(sockfd, buf, N, 0) < 0)
		{
			errlog("fail to send");
		}

		if(strncmp(buf, "quit", 4) == 0)
		{
			break;
		}
		else 
		{
			if(recv(sockfd, buf, N, 0) <= 0)
			{
				errlog("fail to recv");
			}

			printf("server >>> %s\n", buf);
		}
	}


	return 0;
}
