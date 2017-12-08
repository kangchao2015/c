#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>


pthread_mutex_t mutex;  //互斥锁
pthread_cond_t cond;   //条件变量

//全局变量就是线程之间的共享资源
int value_1;
int value_2;
char buf[32] = {0};
//线程函数

void *pthread_fun(void *arg)
{
	while(1)
	{
		//申请操作
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
#if 0
		if(value_1 == value_2)
		{
			printf("value_1 = %d, value_2 = %d \n", value_1, value_2);
		}
#endif
		printf("--> %s\n", buf);
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, const char *argv[])
{
	pthread_t tid;
	int count = 0;
	
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		perror("fail to pthread_mutex_init");
		exit(1);
	}
	if(pthread_cond_init(&cond, NULL) != 0)
	{
		perror("fail to pthread_cond_init");
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
		sleep(1);
		pthread_mutex_lock(&mutex);
#if 0
		value_1 = count;
		value_2 = count;
		count++;
#endif
		fgets(buf, 32, stdin);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_join(tid, NULL);

	return 0;
}
