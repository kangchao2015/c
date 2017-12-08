#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linknode,*linknode_t;

linknode_t stack_create();
int stack_push(linknode_t s,datatype value);
datatype stack_pop(linknode_t s);
int stack_empty(linknode_t s);
datatype stack_top(linknode_t s);
void stack_clean(linknode_t s);
void stack_free(linknode_t s);

int main(int argc, const char *argv[])
{
	linknode_t s = NULL;
	if((s = stack_create()) == NULL)
	{
		printf("fail to stack_create\n");
		return -1;
	}
	
	stack_push(s,10);
	stack_push(s,20);
	stack_push(s,30);
	stack_push(s,40);
	stack_push(s,50);

	printf("pop:%d\n",stack_pop(s));
	printf("top:%d\n",stack_top(s));
	stack_free(s);
	return 0;
}

linknode_t stack_create()
{
	linknode_t s = NULL;
	if((s = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("malloc failed\n");
		return NULL;
	}

	s->next = NULL;
	return s;
}

int stack_push(linknode_t s,datatype value)
{
	linknode_t p = NULL;
	if((p = (linknode_t)malloc(sizeof(linknode))) == NULL)
	{
		printf("fail to malloc node\n");
		return -1;
	}

	p->data = value;
	p->next = s->next;
	s->next = p;
	return 0;
}

datatype stack_pop(linknode_t s)
{
	linknode_t p = s->next;

	if(stack_empty(s))
	{
		printf("stack is empty\n");
		return -1;
	}

	datatype tmp = p->data;
	s->next = p->next;
	free(p);
	p = NULL;
	return tmp;
}

int stack_empty(linknode_t s)
{
	return s->next == NULL;
}

datatype stack_top(linknode_t s)
{
	return s->next->data;
}

void stack_clean(linknode_t s)
{
	while(!stack_empty(s))
	{
		printf("pop:%d\n",stack_pop(s));
	}
}

void stack_free(linknode_t s)
{
	stack_clean(s);
	free(s);
	s = NULL;
}
