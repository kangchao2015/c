#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, const char *argv[])
{
	DIR * dir = NULL;
	struct dirent *d = NULL;

	if((dir = opendir(argv[1])) == NULL)
	{
		perror("fail to opendir");
		return -1;
	}

	while((d = readdir(dir)) != NULL)
	{
		printf("%s\n",d->d_name);
	}

	closedir(dir);
	return 0;
}
