#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	time_t t;
	struct tm* mytm = NULL;
	FILE *fp = NULL;
	char buf[32] = {0};
	int count = 0;
	if((fp = fopen("test.txt","a+")) == NULL)
	{
		fprintf(stderr,"fail to fopen\n");
		return -1;
	}
	
	while(fgets(buf,32,fp) != NULL)
	{
		if(buf[strlen(buf) - 1] == '\n')
			count++;
	}


	while(1)
	{
		t = time(NULL);  //time(&t);
		mytm = localtime(&t);
		fprintf(fp,"%d  %d-%d-%d  %d:%d:%d\n",++count,mytm->tm_year + 1900,mytm->tm_mon + 1,mytm->tm_mday,\
				mytm->tm_hour,mytm->tm_min,mytm->tm_sec);
		fflush(NULL);
		sleep(1);
	}
	return 0;
}
