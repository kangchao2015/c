#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = NULL;
	int a[] = {1,2,3,4},b[4],i;
	size_t bytes;

	if((fp = fopen("test","w+")) == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	bytes = fwrite(a,sizeof(int),2,fp);
	printf("bytes = %d\n",bytes);

	rewind(fp);
	bytes = fread(b,sizeof(int),4,fp);
	printf("bytes = %d\n",bytes);
	
	for(i = 0;i < 4;i++)
	{
		printf("b[%d] = %d\n",i,b[i]);
	}
	fclose(fp);
	return 0;
}
