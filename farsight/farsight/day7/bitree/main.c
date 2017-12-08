#include "bitree.h"

int main(int argc, const char *argv[])
{
	bitree_t r = NULL;
	if((r = bitree_create()) == NULL)
	{
		printf("fail to bitree_create\n");
		return -1;
	}

	preorder(r);
	putchar(10);

	inorder(r);
	putchar(10);

	postorder(r);
	putchar(10);

	levelorder(r);
	putchar(10);
	return 0;
}
