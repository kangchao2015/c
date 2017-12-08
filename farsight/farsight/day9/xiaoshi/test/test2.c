#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#define N 64

int main(int argc, const char *argv[])
{
	FILE *fp;
	int i=1,n,m=0;
	int a[N];
	time_t t;
	struct tm *p;
	a[5]=66;

	if((fp=fopen("/home/linux/shi/day9/textfile","a+"))==NULL)
	{
		fprintf(stderr,"fopen() failed:%s\n",strerror(errno));
		return -1;
	}
	n=fgetc(fp);
	while(n!=EOF)
	{
		n=fgetc(fp);
		if(n==10)
		{
			i++;
		}
	}
	fclose(fp);
	while(1)
	{
		fp=fopen("textfile","a+");
		time(&t);
		p=localtime(&t);
		a[0]=1900+p->tm_year;
		a[1]=1+p->tm_mon;
		a[2]=p->tm_mday;
		a[3]=p->tm_hour;
		a[4]=p->tm_min;
		if(a[5]!=p->tm_sec)
		{
			a[5]=p->tm_sec;
			fprintf(fp,"%d.",i);
			fprintf(fp,"%d-%d-%d ",a[0],a[1],a[2]);
			fprintf(fp,"%d:%d:%d\n",a[3],a[4],a[5]);
			i++;
			printf("a[5]=%d\n",a[5]);
		}
		fclose(fp);
	}

	return 0;
}
