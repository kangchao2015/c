#include <stdio.h>
#include <stdlib.h>

#define N 64

typedef int datatype;
typedef struct  
{
	datatype data[N];
	int last;
}sqlist;

sqlist * list_create(); 
int list_insert(sqlist *L,datatype value);
//满----1    没有满-----0
int list_full(sqlist *L);
int list_insert_pos(sqlist *L,int pos,datatype value);
void list_show(sqlist *L);
int list_delete(sqlist *L,int pos);
//空----1    非空----0
int list_empty(sqlist *L);
int list_replace(sqlist *L,datatype old,datatype new);
int list_search(sqlist *L,datatype value);
void list_union(sqlist *La,sqlist *Lb);

int main(int argc, const char *argv[])
{
	sqlist *La = NULL,*Lb = NULL;
	if((La = list_create()) == NULL)
	{
		printf("fail to list_create\n");
		return -1;
	}
	if((Lb = list_create()) == NULL)
	{
		printf("fail to list_create\n");
		return -1;
	}

	list_insert(La,1);
	list_insert(La,2);
	list_insert(La,3);
	list_insert(La,4);
	list_insert(La,5);
	list_show(La);

	list_insert(Lb,4);
	list_insert(Lb,5);
	list_insert(Lb,6);
	list_show(Lb);

	list_union(La,Lb);
	list_show(La);
	list_show(Lb);
	return 0;
}

sqlist * list_create()
{
	sqlist *L = NULL;
	L = (sqlist *)malloc(sizeof(sqlist));
	if(L == NULL)
	{
		printf("fail to malloc\n");
		return NULL;
	}

	L->last = -1;
	return L;
}

int list_insert(sqlist *L,datatype value)
{
	if(list_full(L))
	{
		printf("list is full\n");
		return -1;
	}
	L->data[L->last + 1] = value;
	L->last++;
	return 0;
}

int list_full(sqlist *L)
{
	return L->last == N - 1 ? 1 : 0;
}

int list_insert_pos(sqlist *L,int pos,datatype value)
{
	if(list_full(L))
	{
		printf("list is full\n");
		return -1;
	}
	
	if(pos < 0 || pos > L->last + 1)
	{
		printf("pos error\n");
		return -1;
	}
	int i;
	for(i = L->last + 1;i > pos;i--)
		L->data[i] = L->data[i - 1];

	L->data[pos] = value;
	L->last++;
	return 0;
}

void list_show(sqlist *L)
{
	int i = 0;
	for(i = 0;i < L->last + 1;i++)
	{
		printf("%d ",L->data[i]);
	}
	puts("");
}

int list_delete(sqlist *L,int pos)
{
	if(list_empty(L))
	{
		printf("list is empty");
		return -1;
	}

	if(pos < 0 || pos > L->last)
	{
		printf("pos error\n");
		return -1;
	}
	
	int i ;
	for(i = pos;i < L->last;i++)
		L->data[i] = L->data[i + 1];

	L->last--;
	return 0;
}
//空----1    非空----0
int list_empty(sqlist *L)
{
	return L->last == -1;
}

int list_replace(sqlist *L,datatype old,datatype new)
{
	int i;
	for(i = 0;i <= L->last;i++)
	{
		if(L->data[i] == old)
		{
			L->data[i] = new;
			return 0;
		}
	}
	return -1;
}

int list_search(sqlist *L,datatype value)
{
	int i = 0;
	for(i = 0;i <= L->last;i++)
	{
		if(L->data[i] == value)
			return i;
	}
	return -1;
}

void list_union(sqlist *La,sqlist *Lb)
{
	int i;
	for(i = 0;i <= Lb->last;i++)
	{
		if(list_search(La,Lb->data[i]) == -1)
		{
			list_insert(La,Lb->data[i]);
		}
	}
}
