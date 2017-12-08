//浪费尾结点
#include <stdio.h>
#include <stdlib.h>

#define N 64
typedef int datatype;
typedef struct 
{
	datatype data[N];
	int front;
	int rear;
}queue,*queue_t;

queue_t queue_create();
int enqueue(queue_t q,datatype value);
int queue_full(queue_t q);
datatype dequeue(queue_t q);
int queue_empty(queue_t q);
void queue_clear(queue_t q);
void queue_free(queue_t q);

int main(int argc, const char *argv[])
{
	queue_t q = NULL;
	if((q = queue_create()) == NULL)
	{
		printf("queue_create fail\n");
		return -1;
	}

	enqueue(q,10);
	enqueue(q,20);
	enqueue(q,30);
	enqueue(q,40);
	enqueue(q,50);

	printf("dequeue:%d\n",dequeue(q));
	return 0;
}

queue_t queue_create()
{
	queue_t q = NULL;
	if((q = (queue_t)malloc(sizeof(queue))) == NULL)
	{
		printf("fail to malloc\n");
		return NULL;
	}

	q->front = 0;
	q->rear = 0;
	return q;
}

int enqueue(queue_t q,datatype value)
{
	if(queue_full(q))
	{
		printf("queue is full\n");
		return -1;
	}

	q->data[q->rear] = value;
	q->rear = (q->rear + 1) % N;
	return 0;
}

int queue_full(queue_t q)
{
	return ((q->rear + 1) % N) == q->front;
}

datatype dequeue(queue_t q)
{	
	datatype tmp;
	if(queue_empty(q))
	{
		printf("queue is empty\n");
		return -1;
	}
	
	tmp = q->data[q->front];
	q->front = (q->front + 1) % N;
	return tmp;
}

int queue_empty(queue_t q)
{
	return q->rear == q->front;
}

void queue_clear(queue_t q)
{
	q->front = q->rear = 0;
}
void queue_free(queue_t q)
{
	free(q);
	q = NULL;
}
