#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define SIZE (sizeof(struct msgbuf) - sizeof(long))

struct msgbuf{
	long mtype;
	int a;
	char b;
};
int main(int argc, char *argv[])
{
	key_t key;

	if((key = ftok(".", 'a')) < 0){
		perror("fail to ftok");
		return -1;
	}

	int msqid;
	struct msgbuf msg;
	if((msqid = msgget(key, IPC_CREAT|IPC_EXCL|0664)) < 0){
		if(errno != EEXIST){
			perror("fail to msgget");
			return -1;
		}
		else{
			msqid = msgget(key, 0664);
		}
	}

	if(msgrcv(msqid, &msg, SIZE, 100, 0) < 0){
		perror("fail to msgrcv");
		return -1;
	}

	printf("a = %d b = %c\n", msg.a, msg.b);

	msgctl(msqid, IPC_RMID, NULL);
	return 0;
}
