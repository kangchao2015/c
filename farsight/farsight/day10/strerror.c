#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	printf("%d\n",errno);
	FILE *fp = NULL;
	if((fp = fopen("test","r")) == NULL)
	{
		printf("%d\n",errno);
		//printf("%s\n",strerror(errno));
		//fprintf(stderr,"fail to fopen :%s\n",strerror(errno));
		perror("fail to fopen");
		return -1;
	}

	fclose(fp);
	return 0;
}
