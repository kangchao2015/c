#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	char buf[10] = {0};

	//fgets(buf,10,stdin);
	//printf("%s\n",buf);
	fp = fopen("test","r");
	if(fp == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	fgets(buf,10,fp);
	printf("%s\n",buf);
	fgets(buf,10,fp);
	printf("%s\n",buf);

	fclose(fp);
	return 0;
}
