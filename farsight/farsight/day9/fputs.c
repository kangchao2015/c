#include <stdio.h>

int main(int argc, const char *argv[])
{
	//fputs("hel\0lo world",stdout);
	//puts("hello w\0orld");
	FILE *fp = NULL;
	if((fp = fopen("test","w")) == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	fputs("hello world",fp);
	fputs("hello world",fp);
	fclose(fp);
	return 0;
}
