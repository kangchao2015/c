#include "bitree.h"
#include "linkqueue.h"

bitree_t bitree_create()
{
	bitree_t r = NULL;
	char ch;
	scanf("%c",&ch);

	if(ch == '#')
		return NULL;

	if((r = (bitree_t)malloc(sizeof(bitree))) == NULL)
	{
		printf("fail to malloc node\n");
		return NULL;
	}

	r->data = ch;

	r->lchild = bitree_create();
	r->rchild = bitree_create();
	return r;
}

void preorder(bitree_t r)
{
	if(r == NULL)
		return;
	printf("%c ",r->data);
	preorder(r->lchild);
	preorder(r->rchild);
}

void inorder(bitree_t r)
{
	if(r == NULL)
		return ;
	inorder(r->lchild);
	printf("%c ",r->data);
	inorder(r->rchild);
}

void postorder(bitree_t r)
{
	if(r == NULL)
		return;

	postorder(r->lchild);
	postorder(r->rchild);
	printf("%c ",r->data);
}

void levelorder(bitree_t r)
{
	queue_t q = NULL;
	bitree_t tmp;
	if((q = queue_create()) == NULL)
		return ;

	printf("%c ",r->data);
	enqueue(q,r);

	while(!queue_empty(q))
	{
		tmp = dequeue(q);
		if(tmp->lchild != NULL)
		{
			printf("%c ",tmp->lchild->data);
			enqueue(q,tmp->lchild);
		}
		if(tmp->rchild != NULL)
		{
			printf("%c ",tmp->rchild->data);
			enqueue(q,tmp->rchild);
		}
	}
}
