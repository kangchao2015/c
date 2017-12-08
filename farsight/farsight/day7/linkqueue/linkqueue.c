#include "linkqueue.h"

queue_t queue_create()
{
	linknode_t p = NULL;
	queue_t lq = NULL;

	if((p = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("fail to malloc node\n");
		return NULL;
	}

	if((lq = (queue_t)malloc(sizeof(queue))) == NULL)
	{
		free(p);
		p = NULL;
		printf("fail to malloc queue \n");
		return NULL;
	}

	p->next = NULL;
	lq->front = p;
	lq->rear = p;
	return lq;
}

int enqueue(queue_t lq,datatype value)
{
	linknode_t p = NULL;
	if((p = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc node failed\n");
		return -1;
	}

	p->data = value;
	p->next = lq->rear->next;  //p->next = NULL;
	lq->rear->next = p;

	lq->rear = p;   //lq->rear = lq->rear->next;
	return 0;
}

datatype dequeue(queue_t q)
{
	if(queue_empty(q))
	{
		printf("queue is empty\n");
		return -1;
	}
	datatype t;
	linknode_t tmp = q->front;
	q->front = q->front->next;
	t = q->front->data;
	free(tmp);
	tmp = NULL;
	return t;
}

int queue_empty(queue_t q)
{
	return q->front == q->rear;
}

void queue_clear(queue_t q)
{
	while(!queue_empty(q))
	{
		printf("%d ",dequeue(q));
	}
	putchar(10);
}

void queue_free(queue_t q)
{
	queue_clear(q);
	free(q->front);
	q->front = NULL;
	q->rear = NULL;
	free(q);
	q = NULL;
}
