#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int ch;
	//ch = fgetc(stdin);
	//printf("%c\n",ch);
	fp = fopen("test","r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}
	
	ch = fgetc(fp);
	printf("%c\n",ch);
	ch = fgetc(fp);
	printf("%c\n",ch);
	ch = fgetc(fp);
	printf("%c\n",ch);
	fclose(fp);
	return 0;
}
