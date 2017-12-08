#ifndef BITREE_H_
#define BITREE_H_
#include <stdio.h>
#include <stdlib.h>

typedef char datatype_t;
typedef struct node_t
{
	datatype_t data;
	struct node_t *lchild;
	struct node_t *rchild;
}bitree,*bitree_t;

bitree_t bitree_create();
void preorder(bitree_t r);
void inorder(bitree_t r);
void postorder(bitree_t h);
void levelorder(bitree_t r);
#endif
