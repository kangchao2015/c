#include <stdio.h>
#include <stdlib.h>

#define N 64
typedef int datatype;

typedef struct
{
	datatype data[N];
	int top;
}sqstack,*sqstack_t;

sqstack_t stack_create();
int stack_push(sqstack_t s,datatype value);
int stack_full(sqstack_t s);
datatype stack_pop(sqstack_t s);
int stack_empty(sqstack_t s);
datatype stack_top(sqstack_t s);
void stack_clean(sqstack_t s);
void stack_free(sqstack_t s);

int main(int argc, const char *argv[])
{
	sqstack_t s = NULL;
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
	return 0;
}

sqstack_t stack_create()
{
	sqstack_t s = NULL;
	if((s = (sqstack_t)malloc(sizeof(sqstack))) == NULL)
	{
		printf("fail to malloc\n");
		return NULL;
	}

	s->top = -1;
	return s;
}

int stack_push(sqstack_t s,datatype value)
{
	if(stack_full(s))
	{
		printf("stack is full\n");
		return -1;
	}

	s->data[s->top + 1] = value;
	s->top++;
	return 0;
}

int stack_full(sqstack_t s)
{
	return s->top == N - 1;
}

datatype stack_pop(sqstack_t s)
{
	if(stack_empty(s))
	{
		printf("stack is empty\n");
		return -1;
	}
	//i = s->data[s->top];
	s->top--;
	return s->data[s->top + 1];
}

int stack_empty(sqstack_t s)
{
	return s->top == -1;
}

datatype stack_top(sqstack_t s)
{
	return s->data[s->top];
}
void stack_clean(sqstack_t s)
{
	s->top = -1;
}

void stack_free(sqstack_t s)
{
	free(s);
	s = NULL;
}
