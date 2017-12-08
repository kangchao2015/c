#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int ch;
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}
	while((ch = fgetc(fp)) != EOF)
	{
		fputc(ch,stdout);
	}
	fclose(fp);
	return 0;
}
