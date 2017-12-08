#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	fp = fopen("test","r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	fclose(fp);
	fclose(fp); //不要多重释放
	return 0;
}
