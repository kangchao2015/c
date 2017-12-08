#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, const char *argv[])
{
	struct stat buf;
	struct passwd *pass = NULL;
	struct group *grp = NULL;
	char *p = NULL;

	if(stat(argv[1],&buf) < 0)
	{
		perror("fail to stat");
		return -1;
	}

	if(S_ISREG(buf.st_mode))
	{
		putchar('-');
	}
	if(S_ISDIR(buf.st_mode))
	{
		putchar('d');
	}
	if(S_ISCHR(buf.st_mode))
	{
		putchar('c');
	}
	if(S_ISBLK(buf.st_mode))
	{
		putchar('b');
	}
	if(S_ISFIFO(buf.st_mode))
	{
		putchar('p');
	}
	if(S_ISLNK(buf.st_mode))
	{
		putchar('l');
	}
	if(S_ISSOCK(buf.st_mode))
	{
		putchar('s');
	}

	if(buf.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');
	if(buf.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if(buf.st_mode & S_IXUSR)
		putchar('x');
	else
		putchar('-');

	if(buf.st_mode & S_IRGRP)
		putchar('r');
	else
		putchar('-');
	if(buf.st_mode & S_IWGRP)
		putchar('w');
	else
		putchar('-');
	if(buf.st_mode & S_IXGRP)
		putchar('x');
	else
		putchar('-');

	if(buf.st_mode & S_IROTH)
		putchar('r');
	else
		putchar('-');
	if(buf.st_mode & S_IWOTH)
		putchar('w');
	else
		putchar('-');
	if(buf.st_mode & S_IXOTH)
		putchar('x');
	else
		putchar('-');
	
	putchar(' ');

	printf("%d ",buf.st_nlink);

	pass = getpwuid(buf.st_uid);
	printf("%s ",pass->pw_name);

	grp = getgrgid(buf.st_gid);
	printf("%s ",grp->gr_name);

	printf("%ld ",buf.st_size);

	p = ctime(&buf.st_ctime);
	printf("%.12s ",p + 4); //&p[4]

	printf("%s\n",argv[1]);
	return 0;
}
