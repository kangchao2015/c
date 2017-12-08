#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;

	fp = fopen("test","w");
	if(fp == NULL)
	{
		fprintf(stderr,"fail to fopen\n");
		return -1;
	}

	fprintf(fp,"hello world\n");
	fflush(fp);
	while(1)
		;
	return 0;
}
