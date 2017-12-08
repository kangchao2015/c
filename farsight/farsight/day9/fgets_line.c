#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	char buf[10] = {0};
	int count = 0;

	fp = fopen("test","r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	while(fgets(buf,10,fp) != NULL)
	{
		if(buf[strlen(buf) - 1] == '\n')
			count++;
	}	

	printf("count = %d\n",count);
	fclose(fp);
	return 0;
}
