#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem;  //信号量
sem_t sem1;  //信号量
//全局变量就是线程之间的共享资源
int value_1;
int value_2;

//线程函数

void *pthread_fun(void *arg)
{
	while(1)
	{
		//申请操作
		sem_wait(&sem);
		if(value_1 == value_2)
		{
			printf("value_1 = %d, value_2 = %d \n", value_1, value_2);
		}
		sem_post(&sem1);
	}
}

int main(int argc, const char *argv[])
{
	pthread_t tid;
	int count = 0;
	
	//创建信号量
	if(sem_init(&sem, 0, 0) < 0)
	{
		perror("fail to sem_init");
		exit(1);
	}

	//创建信号量1,资源的数量为1
	if(sem_init(&sem1, 0, 1) < 0)
	{
		perror("fail to sem_init  sem1");
		exit(1);
	}
	//线程的创建
#if 1
	if(pthread_create(&tid, NULL, pthread_fun, NULL) != 0)
	{
		perror("fail to pthread_create");
		exit(1);
	}
#endif
	//线程处理函数，对线程占用的内存空间进行释放,等待线程结束，如果不结束，则会阻塞等待
	//如果等待到了，则会立即返回
	while(1)
	{
		sem_wait(&sem1);
		value_1 = count;
		value_2 = count;
		count++;
		sem_post(&sem);
	}
	pthread_join(tid, NULL);

	return 0;
}
