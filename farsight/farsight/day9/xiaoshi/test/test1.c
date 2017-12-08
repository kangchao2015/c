#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define N 10

int main(int argc, const char *argv[])
{
	FILE *fp;
	time_t p;
	struct tm *t;
	int a[N];
	int i=1,n;
	if((fp=fopen("textfile","a+"))==NULL)
	{
		printf("fopen is fail\n");
		return -1;
	}
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
		sleep(1);
		fp=fopen("textfile","a+");
		time(&p);
		t=localtime(&p);
 		a[0]=1900+t->tm_year;
		a[1]=1+t->tm_mon;
		a[2]=t->tm_mday;
		a[3]=t->tm_hour;
		a[4]=t->tm_min;
		a[5]=t->tm_sec;
		fprintf(fp,"%d.",i);
		fprintf(fp,"%d-%d-%d ",a[0],a[1],a[2]);
		fprintf(fp,"%d:%d:%d\n",a[3],a[4],a[5]);
		printf("a[5]=%d\n",a[5]);	
		i++;
		fclose(fp);
	}
	return 0;
}
