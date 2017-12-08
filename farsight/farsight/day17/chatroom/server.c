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

//节点类型
typedef struct node
{
	struct sockaddr_in addr;  //用来存储客户端IP地址和端口号
	struct node *next;
}linknode, *linklist;

//创建链表节点
linklist link_create(void)
{
	linklist h = (linklist)malloc(sizeof(linknode));
	h->next = NULL;
	return h;
}

//登录函数
void process_login(int sockfd, MSG *msg, linklist h, struct sockaddr_in clientaddr)
{
	linklist p = h->next;
	//拼接字符串
	sprintf(msg->text, "%s login", msg->name);
	//遍历链表，转发给所有客户端
	while(p != NULL)
	{
		sendto(sockfd, msg, sizeof(MSG), 0, (struct sockaddr*)&p->addr, sizeof(clientaddr));
		p = p->next;
	}
	//八把自己添加到链表中
	linklist temp = (linklist)malloc(sizeof(linknode));
	temp->addr = clientaddr;

	temp->next = h->next;
	h->next = temp;
}


//聊天函数
void process_chat(int sockfd, MSG *msg, linklist h, struct sockaddr_in clientaddr)
{
	linklist p = h->next;
	char buf[N] = {0};
	//拼接字符串
	sprintf(buf, "%s said %s", msg->name, msg->text);
	strcpy(msg->text, buf);
	//遍历链表，转发给所有客户端
	while(p != NULL)
	{
		if(memcmp(&p->addr, &clientaddr, sizeof(clientaddr)) == 0)
		{
			p = p->next;
		}
		else
		{
			sendto(sockfd, msg, sizeof(MSG), 0, (struct sockaddr*)&p->addr, sizeof(clientaddr));
			p = p->next;
		}
	}
}
//退出函数
void process_quit(int sockfd, MSG *msg, linklist h, struct sockaddr_in clientaddr)
{
	linklist p = h;
	linklist temp;

	//拼接字符串
	sprintf(msg->text, "%s quit", msg->name);
	//遍历链表，转发给所有客户端
	while(p->next != NULL)
	{
		if(memcmp(&p->next->addr, &clientaddr, sizeof(clientaddr)) == 0)
		{


			temp = p->next;
			p->next = temp->next;
			
			free(temp);
			temp = NULL;
		}
		else
		{
			sendto(sockfd, msg, sizeof(MSG), 0, (struct sockaddr*)&p->next->addr, sizeof(clientaddr));
			p = p->next;
		}
	}
}


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
	//绑定IP地址和端口号，让客户端链接服务器
	if(bind(sockfd, (struct sockaddr*)&serveraddr, len) < 0)
	{
		errlog("fail to bind");
	}

	//创建父子进程，父进程接收数据， 子进程发送数据
	pid = fork();
	if(pid < 0)
	{
		errlog("fail to fork");
	}

	if(pid == 0)//子进程
	{
		strcpy(msg.name, "server");
		msg.type = B;
		while(1)
		{
			fgets(buf, N, stdin);
			buf[strlen(buf) - 1] = '\0';
			strcpy(msg.text, buf);
			sendto(sockfd, &msg, msg_len, 0, (struct sockaddr*)&serveraddr, len);//给父进程发送数据
		}
	}
	else//父进程接收数据
	{

		linklist h = link_create();//创建链表
		while(1)
		{
			recvfrom(sockfd, &msg, msg_len, 0, (struct sockaddr*)&clientaddr, &len);
			printf("%s \n", inet_ntoa(clientaddr.sin_addr));
			switch(msg.type)
			{
			case L:
				process_login(sockfd, &msg, h, clientaddr);
				break;
			case B:
				process_chat(sockfd, &msg, h, clientaddr);
				break;
			case Q:
				process_quit(sockfd, &msg, h, clientaddr);
				break;
			}
		}
	}
	return 0;
}
