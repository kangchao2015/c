#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	long l;

	if((fp = fopen("test","w")) == NULL)
	{
		fprintf(stderr,"fail to fopen\n");
		return -1;
	}

	fseek(fp,10,SEEK_SET);
	l = ftell(fp);
	printf("l = %ld\n",l);
	fclose(fp);
	return 0;
}
