//TCP服务器的实现

#include <stdio.h>  //printf
#include <sys/types.h>
#include <sys/socket.h> //socket,bind,listen,accept,connect,send,recv
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> //inet_addr,htons
#include <stdlib.h> //exit
#include <string.h>
#include <dirent.h>
#include <errno.h> //errno
#include <sys/stat.h>
#include <fcntl.h>

#define N 128
#define errlog(errmsg) do{perror(errmsg);\
						  printf("%s --> %s --> %d\n", __FILE__, __func__, __LINE__);\
				          exit(1);\
						  }while(0)

int do_list(int acceptfd)
{
	DIR *dirp;
	struct dirent *ent;
	char buf[N] = {};
	//打开目录
	if((dirp = opendir(".")) == NULL)
	{
		errlog("fail to opendir");
	}

	//读取目录当中的文件名
	while((ent = readdir(dirp)) != NULL)
	{
		if(ent->d_name[0] == '.')
		{
			continue;
		}

		//每次获取一个文件名，将其发送给客户端
		strcpy(buf, ent->d_name);
		
		if(send(acceptfd, buf, N, 0) < 0)
		{
			errlog("fail to send");
		}
	}

	printf("目录发送完毕\n");
	close(acceptfd);

	return 0;
}

int do_download(int acceptfd, char *filename)
{
	int fd;
	char buf[N] = {};
	ssize_t bytes;

	//打开文件
	if((fd = open(filename, O_RDONLY)) < 0)
	{
		//如果文件不存在，则发送信息
		if(errno == ENOENT)
		{
			strcpy(buf, "NO");
			send(acceptfd, buf, N, 0);
		}
		else
		{
			errlog("fail to open");
		}
	}

	strcpy(buf, "YES");
	send(acceptfd, buf, N, 0);

	//读取文件数据，发送给客户端
	while((bytes = read(fd, buf, N)) > 0)
	{
		send(acceptfd, buf, bytes, 0);

		usleep(25);
	}

	printf("文件发送完毕\n");
	close(acceptfd);
	
	return 0;
}

int do_upload(int acceptfd, char *filename)
{
	int fd;
	char buf[N] = {};
	ssize_t bytes;

	//创建文件
	if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
	{
		errlog("fail to open");
	}

	//每次接收到数据，然后写进去
	while((bytes = recv(acceptfd, buf, N, 0)) > 0)
	{
		write(fd, buf, bytes);

		usleep(15);
	}

	printf("文件上传完毕\n");
	
	close(acceptfd);
	
	return 0;
}

int main(int argc, const char *argv[]) //./a.out 192.168.1.118 9999
{
	int sockfd, acceptfd;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	char buf[N] = {};
	
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

	while(1)
	{

		//第四步：阻塞等待客户端的连接请求
		if((acceptfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen)) < 0)
		{
			errlog("fail to accept");
		}

		printf("%s ---> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//接收客户端发过来的信息

		if(recv(acceptfd, buf, N, 0) <= 0)  //buf = L G P
		{
			errlog("fail to recv");
		}

		printf("recv >>> %s\n", buf);

		switch(buf[0])
		{
		case 'L':
			do_list(acceptfd);
			break;
		case 'G':
			do_download(acceptfd, buf + 2); //G filename
			break;
		case 'P':
			do_upload(acceptfd, buf + 2);
			break;
		}
	}

	close(sockfd);
	return 0;
}
