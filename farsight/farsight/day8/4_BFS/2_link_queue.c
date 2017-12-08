//队列：先进先出
#include "1_link_queue.h"

//创建空的队列
linkqueue_t * linkqueue_create()
{
	linknode_t * head = (linknode_t *)malloc(sizeof(linknode_t)); 		//给头节点开辟空间
	head->next = NULL;

	linkqueue_t *queue = (linkqueue_t *)malloc(sizeof(linkqueue_t));  	//给队列开辟空间
	queue->front = head;
	queue->rear  = head;

	return queue;
}

//入队（尾插法）
int linkqueue_input(linkqueue_t *queue, data_t value)
{
	linknode_t *node = (linknode_t *)malloc(sizeof(linknode_t));
	node->data = value;
	node->next = NULL;

	queue->rear->next = node; 		//最后一个节点与node相连
	queue->rear = node; 			//rear始终指向最后一个节点（队尾）

	return 0;
}

//判断是否为空： 空 return 1； 非空 return 0；
int linkqueue_is_empty(linkqueue_t *queue)
{
	return queue->front->next == NULL? 1 : 0;
}

//出队（头删法）
data_t linkqueue_output(linkqueue_t *queue)
{
	if(linkqueue_is_empty(queue) == 1)
	{
		puts("empty");
		return -1;
	}
	
	linknode_t *temp = queue->front->next; 		//temp：临时记录第一个节点
	queue->front->next = temp->next; 			//头删法

	data_t value = temp->data; 					//value：记录要删除节点的数据段
	free(temp);
	temp = NULL;

#if 1

	if(queue->front->next == NULL)
	{
		queue->rear = queue->front; 		//当删除最后一个节点时，对rear重新赋值，指向队头
	}
#endif

	return value;
}





