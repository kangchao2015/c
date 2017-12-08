#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, const char *argv[])
{
	FILE *fp;

	if((fp=fopen("textfile","r+"))==NULL)
	{
		fprintf(stderr,"fopen() failed:%s\n",strerror(errno));
		return -1;
	}
	fclose(fp);

	return 0;
}


