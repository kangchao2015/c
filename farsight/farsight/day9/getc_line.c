#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int ch,count = 0;
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}
	
	while(1)
	{
		ch = fgetc(fp);
		if(ch == EOF)
			break;
		else if(ch == '\n')
			count++;
	}
	printf("count = %d\n",count);
	fclose(fp);
	return 0;
}
