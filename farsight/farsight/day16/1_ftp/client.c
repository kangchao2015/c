//TCP客户端的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> //inet_addr,htons
#include <stdlib.h> //exit
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 128
#define errlog(errmsg) do{perror(errmsg);\
						  printf("%s --> %s --> %d\n", __FILE__, __func__, __LINE__);\
				          exit(1);\
						  }while(0)

int do_help()
{
	printf("***********************************\n");
	printf("list:查看服务器所在目录的文件名\n");
	printf("get 文件名:下载文件\n");
	printf("put 文件名:上传文件\n");
	printf("quit:退出\n");
	printf("***********************************\n");
	
	return 0;
}

int do_list(struct sockaddr_in serveraddr)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};
 
	//第一步：创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第三步：发送客户端的连接请求
	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
	{
		errlog("fail to accept");
	}

	//将list的请求发送给服务器
	strcpy(buf, "L");
	if(send(sockfd, buf, N, 0) < 0)
	{
		errlog("fail to send");
	}
		
	while(recv(sockfd, buf, N, 0) > 0)
	{
		printf("*** %s\n", buf);
	}

	printf("目录接收完毕\n");
	close(sockfd);

	return 0;
}

int do_download(struct sockaddr_in serveraddr, char *filename)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};
	int fd;
	ssize_t bytes;
 
	//第一步：创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第三步：发送客户端的连接请求
	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
	{
		errlog("fail to accept");
	}

	//发送G filename
	sprintf(buf, "G %s", filename); //buf = G 99.txt
	if(send(sockfd, buf, N, 0) < 0)
	{
		errlog("fail to send");
	}

	recv(sockfd, buf, N, 0);

	if(strncmp(buf, "NO", 2) == 0)
	{
		printf("%s is not exist\n", filename);

		close(sockfd);
		return -1;
	}
	
	//创建文件
	if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
	{
		errlog("fail to open");
	}

	//每次接收数据，写进文件
	while((bytes = recv(sockfd, buf, N, 0)) > 0)
	{
		write(fd, buf, bytes);

		usleep(15);
	}

	printf("文件下载完毕\n");
	close(sockfd);

	return 0;
}

int do_upload(struct sockaddr_in serveraddr, char *filename)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};
	int fd;
	ssize_t bytes;
 
	//第一步：创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errlog("fail to socket");
	}

	//第三步：发送客户端的连接请求
	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
	{
		errlog("fail to accept");
	}

	//将文件名发送给服务器
	sprintf(buf, "P %s", filename);
	send(sockfd, buf, N, 0);

	//打开文件
	if((fd = open(filename, O_RDONLY)) < 0)
	{
		errlog("fail to open");
	}

	//每次读取内容并发送给服务器
	while((bytes = read(fd, buf, N)) > 0)
	{
		send(sockfd, buf, bytes, 0);

		usleep(25);
	}
	
	printf("文件上传完毕\n");
	close(sockfd);
	
	return 0;
}

int main(int argc, const char *argv[]) //./a.out 192.168.1.118 9999
{
	struct sockaddr_in serveraddr;
	char buf[N] = {};

	if(argc < 3)
	{
		printf("you must input 3 arguments\n");
		exit(1);
	}

	//第二步：填充服务器网络信息结构体
	//inet_addr：将点分十进制IP地址转化为网络识别的
	//htohs：将主机字节序转化为网络字节序
	//atoi：将数字型字符串转化为整型数据
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));


	printf("************************\n");
	printf("***请输入help查看选项***\n");
	printf("************************\n");

	while(1)
	{
		printf("please input >>> ");

		fgets(buf, N, stdin);
		buf[strlen(buf) - 1] = '\0';

		if(strncmp(buf, "help", 4) == 0)
		{
			do_help();
		}
		else if(strncmp(buf, "list", 4) == 0)
		{
			do_list(serveraddr);
		}
		else if(strncmp(buf, "get", 3) == 0)  //get filename
		{
			do_download(serveraddr, buf + 4);
		}
		else if(strncmp(buf, "put", 3) == 0)
		{
			do_upload(serveraddr, buf + 4);
		}
		else if(strncmp(buf, "quit", 4) == 0)
		{
			break;
		}
		else
		{
			printf("error:please input current option\n");
		}
	}


	return 0;
}
