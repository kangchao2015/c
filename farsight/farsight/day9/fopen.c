#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	fp = fopen("test","r");
	setbuf(stdout,NULL);
	if(fp == NULL)
	{
		printf("fail to fopen");
		while(1)
			;
		return -1;
	}

	return 0;
}
