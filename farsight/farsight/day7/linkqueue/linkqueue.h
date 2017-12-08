//浪费头结点
#ifndef LINKQUEUE_T_
#define LINKQUEUE_T_

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linknode,*linknode_t;

typedef struct
{
	linknode_t front;
	linknode_t rear;
}queue,*queue_t;

queue_t queue_create();
int enqueue(queue_t q,datatype value);
datatype dequeue(queue_t q);
int queue_empty(queue_t q);
void queue_clear(queue_t q);
void queue_free(queue_t q);
#endif

