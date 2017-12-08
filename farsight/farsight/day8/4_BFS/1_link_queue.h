#ifndef _QUEUE_H_
#define _QUEUE_H_


//队列：先进先出

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

//节点的类型
typedef struct node{
	data_t data;
	struct node* next;
}linknode_t;

//队列的类型
typedef struct{
	linknode_t *front; 		//队头的指针：头节点的地址
	linknode_t *rear; 		//队尾的指针：最后一个节点的地址
}linkqueue_t;


//创建空的队列
linkqueue_t * linkqueue_create();

//入队（尾插法）
int linkqueue_input(linkqueue_t *queue, data_t value);

//判断是否为空： 空 return 1； 非空 return 0；
int linkqueue_is_empty(linkqueue_t *queue);

//出队（头删法）
data_t linkqueue_output(linkqueue_t *queue);

#endif



