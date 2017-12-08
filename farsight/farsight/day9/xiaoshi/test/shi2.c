#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp;
	if(argc<2)
	{
		fprintf(stdout,"usage:%s filename\n",argv[0]);
		return -1;
	}
	if((fp=fopen(argv[1],"r+"))==NULL)
	{
		perror("fopen");
		return -1;
	}
	printf("before freopen\n");
	freopen(argv[1],"w",stdout);
	printf("after freopen\n");
	freopen("/dev/tty","w",stdout);
	printf("end main\n");

	return 0;
}
