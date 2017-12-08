#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//线程函数

void *pthread_fun(void *arg)
{
	int count;
	count = *(int *)arg;
	while(count--)
	{
		printf("hello world \n");
		sleep(1);
		if(count == 5)
		pthread_exit("pthread exit");
	}
}

int main(int argc, const char *argv[])
{
	pthread_t tid;
	//线程的创建
#if 0
	if(pthread_create(&tid, NULL, pthread_fun, NULL) != 0)
	{
		perror("fail to pthread_create");
		exit(1);
	}
#endif
	int num = 10;
	if(pthread_create(&tid, NULL, pthread_fun, &num) != 0)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	//线程处理函数，对线程占用的内存空间进行释放,等待线程结束，如果不结束，则会阻塞等待
	//如果等待到了，则会立即返回
#if 0
	pthread_join(tid, NULL);
#endif

	void *ret;
	pthread_join(tid, &ret);

	printf("--> %s \n", (char *)ret);
	//while(1);
	return 0;
}
