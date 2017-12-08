//HASH表：多链表的集合，特点快！

#include <stdio.h>
#include <stdlib.h>

#define P 13 			//数据个数是N=12， N*=4/3, 以内的最大质数

typedef int data_t;

//节点类型
typedef struct node{
	data_t data;
	struct node *next;
}linknode_t;

typedef linknode_t ** HASH_t;

//创建一个空的HASH表
HASH_t linkHASH_create()
{
	int i;
	HASH_t H = (HASH_t)malloc(P *sizeof(linknode_t*)); 				//开辟头节点指针的空间

	for(i=0; i<P; i++)
	{
		H[i] = (linknode_t *)malloc(sizeof(linknode_t)); 			//循环开辟头节点
		H[i]->next = NULL; 											//头节点的地址段为NULL
	}

	return H;
}

//插入数据
int linkHASH_insert(HASH_t H, data_t value)
{
	int key = value % P;
	linknode_t *temp = H[key];  		//temp临时记录相应链表头节点地址

	linknode_t *node = (linknode_t *)malloc(sizeof(linknode_t));
	node->data = value;

	//按顺序插入
	while(temp->next != NULL && temp->next->data < value) 		//数据最大，插入NULL前；数据不是最大，判断数据段
	{
		temp = temp->next;
	}

	node->next = temp->next;
	temp->next = node;

	return 0;
}

//打印hash表
int linkHASH_show(HASH_t H)
{
	int i;
	linknode_t *temp = NULL;

	for(i=0; i<P; i++)
	{
		temp = H[i];

		printf("H[%2d] :",i);

		while(temp->next != NULL)
		{
			temp = temp->next;
			printf("%d ",temp->data);
		}
		putchar(10);
	}

	return 0;
}

//查找
int linkHASH_serach(HASH_t H, data_t value)
{
	int key = value % P;
	linknode_t *temp = H[key];

	while(temp->next != NULL)
	{
		temp = temp->next;
		if(temp->data == value)
		{
			return 1;
		}
	}

	return 0;
}


int main(int argc, const char *argv[])
{
	HASH_t h = linkHASH_create();
	linkHASH_insert(h,11);
	linkHASH_insert(h,12);
	linkHASH_insert(h,35);
	linkHASH_insert(h,0);
	linkHASH_insert(h,56);
	linkHASH_insert(h,3);
	linkHASH_insert(h,30);
	linkHASH_insert(h,19);
	linkHASH_insert(h,23);
	linkHASH_insert(h,6);
	linkHASH_insert(h,4);
	linkHASH_insert(h,17);
	linkHASH_show(h);

	if(linkHASH_serach(h,36))
	{
		puts("存在");
	}
	else
	{
		puts("不存在");
	}
	
	return 0;
}

