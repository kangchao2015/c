#include "linkqueue.h"

int main(int argc, const char *argv[])
{
	queue_t lq = NULL;
	if((lq = queue_create()) == NULL)
	{
		printf("queue_create fail\n");
		return -1;
	}

	enqueue(lq,10);
	enqueue(lq,20);
	enqueue(lq,30);
	enqueue(lq,40);
	enqueue(lq,50);
	printf("dequeue:%d\n",dequeue(lq));
	printf("dequeue:%d\n",dequeue(lq));

	queue_free(lq);
	return 0;
}


