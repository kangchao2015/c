#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int a = 99;
	//fputc(98,stdout);
	//fputc('a',stdout);
	//fputc(a,stdout);
	fp = fopen("test","w");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}
	fputc(98,fp);
	fputc('a',fp);
	fputc(a,fp);

	fclose(fp);
	return 0;
}
