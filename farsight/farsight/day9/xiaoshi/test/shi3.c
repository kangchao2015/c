#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int ch;
	FILE *fp;
	if((fp=fopen("/home/linux/shi/day9/textfile","r+"))==NULL)
	{
		perror("Open file file:\n");

		return -1;
	}
//	while((ch=getchar())!=EOF)
//	{
//		fputc(ch,fp);
//	}
//	rewind(fp);

	while((ch=fgetc(fp))!=EOF)
	{
		putchar(ch);
	}
	fclose(fp);
	printf("%d\n",time());
	return 0;
}
