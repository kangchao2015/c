#include "head.h"

#define errlog(err) do{ perror(err); exit(1); } while(0)

#define N 128

#define L 1
#define B 2
#define Q 3

//消息类型
typedef struct
{
	char type;
	char name[N];
	char text[N];
} MSG;



int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t len = sizeof(serveraddr);
	pid_t pid;
	MSG msg;
	int msg_len = sizeof(msg);
	char buf[N] = {0};
	//设定通信标准，基于UDP实现聊天室
	sockfd  = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		errlog("fail to socket");
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	fgets(msg.name, N, stdin); //名字hh
	msg.name[strlen(msg.name) - 1] = '\0';
	
	msg.type = L;  //类型  登录

	sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr*)&serveraddr, len);

	//创建父子进程，父进程接收数据， 子进程发送数据
	pid = fork();
	if(pid < 0)
	{
		errlog("fail to fork");
	}

	if(pid == 0)//子进程
	{
		while(1)
		{
			fgets(buf, N, stdin);
			buf[strlen(buf) - 1] = '\0';
			strcpy(msg.text, buf);
			if(strncmp(buf, "quit", 4) == 0)
			{
				msg.type = Q;

				sendto(sockfd, &msg, msg_len, 0, (struct sockaddr*)&serveraddr, len);//给父进程发送数据
				close(sockfd);
				kill(getppid(), SIGKILL);
				exit(0);
			}
			msg.type = B;
			sendto(sockfd, &msg, msg_len, 0, (struct sockaddr*)&serveraddr, len);//给父进程发送数据
		}
	}
	else//父进程接收数据
	{
	
		while(1)
		{
			recvfrom(sockfd, &msg, msg_len, 0, (struct sockaddr*)&serveraddr, &len);//给父进程发送数据
			printf("%s \n", msg.text);	
		}
	}
	return 0;
}
