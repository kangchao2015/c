#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp_r = NULL,*fp_w = NULL;
	char buf[32] = {0};
	size_t bytes;

	if((fp_r = fopen(argv[1],"r")) == NULL)
	{
		printf("fail to fopen\n");
		return -1;
	}

	if((fp_w = fopen(argv[2],"w")) == NULL)
	{
		fclose(fp_r);
		printf("fail to fopen\n");
		return -1;
	}
	
	while(1)
	{
		bytes = fread(buf,sizeof(char),32,fp_r);
		if(bytes == 0)
			break;
		else
			fwrite(buf,sizeof(char),bytes,fp_w);
	}

	if(feof(fp_r))
	{
		printf("end\n");
	}

	if(ferror(fp_r))
	{
		printf("error\n");
	}

	clearerr(fp_r);
	fclose(fp_r);
	fclose(fp_w);
	return 0;
}
