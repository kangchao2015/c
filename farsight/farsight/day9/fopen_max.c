#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int count = 0;
	fclose(stdin);
	//fclose(stdout);
	fclose(stderr);
	while(1)
	{
		fp = fopen("test","w");
		if(fp == NULL)
		{
			printf("fail to fopen\n");
			break;
		}
		count++;
	}

	printf("count = %d\n",count);
	return 0;
}
