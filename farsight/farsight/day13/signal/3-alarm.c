#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	unsigned int ret;
	ret = alarm(5);
	printf("ret = %d\n", ret);

	sleep(2);

	ret = alarm(10);
	printf("ret = %d\n", ret);
	while(1)
		;
	return 0;
}
