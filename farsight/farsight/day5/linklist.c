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
