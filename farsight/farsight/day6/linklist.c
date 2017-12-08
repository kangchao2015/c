#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node
{
	datatype data;
	struct node *next;
}linknode,*linknode_t;

linknode_t list_create();
int list_insert(linknode_t H,datatype value);
void list_show(linknode_t H);
int list_delete(linknode_t H);
int list_empty(linknode_t H);
int list_insert_pos(linknode_t H,datatype value,int pos);
int list_delete_value(linknode_t H,datatype value);
int list_replace(linknode_t H,datatype old,datatype new);
int list_search(linknode_t H,datatype value);
void list_reserce(linknode_t H);

int main(int argc, const char *argv[])
{
	linknode_t H = NULL;
	if((H = list_create()) == NULL)
	{
		printf("fail to list_create\n");
		return -1;
	}

	list_insert(H,10);
	list_insert(H,20);
	list_insert(H,30);
	list_insert(H,40);
	list_insert(H,50);
	list_show(H);

	list_delete(H);
	list_show(H);

	list_insert_pos(H,100,2);
	list_show(H);

	list_delete_value(H,100);
	list_show(H);

	list_replace(H,20,100);
	list_show(H);

	printf("search:%d\n",list_search(H,100));

	list_reserce(H);
	list_show(H);
	return 0;
}

linknode_t list_create()
{
	linknode_t H = NULL;
	if((H = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("fail to malloc\n");
		return NULL;
	}
	
	H->next = NULL;
	return H;
}

int list_insert(linknode_t H,datatype value)
{
	linknode_t p = NULL;
	if((p = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("fail to malloc node\n");
		return -1;
	}

	p->data = value;
	p->next = H->next;
	H->next = p;
	return 0;
}

void list_show(linknode_t H)
{
	while(H->next != NULL)
	{
		printf("%d ",H->next->data);
		H = H->next;
	}
	printf("\n");
}

int list_delete(linknode_t H)
{
	linknode_t p = NULL;

	if(list_empty(H))
	{
		printf("list is empty\n");
		return -1;
	}
	p = H->next;

	//H->next = H->next->next;
	H->next = p->next;
	free(p);
	p = NULL;
	return 0;
}

int list_empty(linknode_t H)
{
	return H->next == NULL;
}

int list_insert_pos(linknode_t H,datatype value,int pos)
{
	linknode_t p = H,q = NULL;
	int i;
	for(i = 0;i < pos;i++)
	{
		p = p->next;
	}
	
	if((q = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("fail to malloc node\n");
		return -1;
	}

	q->data = value;
	q->next = p->next;
	p->next = q;
	return 0;
}

int list_delete_value(linknode_t H,datatype value)
{
	linknode_t p = H->next,q = NULL;

	while(p != NULL)
	{
		if(p->data == value)
		{
			p->data = p->next->data;
			q = p->next;
			p->next = q->next;
			free(q);
			q = NULL;
			return 0;
		}
		else
		{
			p = p->next;
		}
	}
	return -1;
}

int list_replace(linknode_t H,datatype old,datatype new)
{
	linknode_t p = H->next;
	while(p != NULL)
	{
		if(p->data == old)
		{
			p->data = new;
			return 0;
		}
		else
		 	p = p->next;
	}
	return -1;
}

int list_search(linknode_t H,datatype value)
{
	linknode_t p = H->next;
	while(p != NULL)
	{
		if(p->data == value)
			return 1;
		else
			p = p->next;
	}
	return 0;
}

void list_reserce(linknode_t H)
{
	linknode_t p = H->next,q = NULL; //p标记要拿的结点，q标记链表剩下的结点
	H->next = NULL;
	while(p != NULL)
	{
		q = p->next;
		p->next = H->next;
		H->next = p;
		p = q;
	}
}
