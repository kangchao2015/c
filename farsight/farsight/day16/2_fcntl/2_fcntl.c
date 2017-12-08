#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char buf[32] = {};

	//第一步：获取标志位
	int flags;
	if((flags = fcntl(0, F_GETFL)) < 0)
	{
		perror("fail to fcntl");
		exit(1);
	}

	//第二步：修改标志位
	flags = flags | O_NONBLOCK;

	//将新的标志位写进去
	if(fcntl(0, F_SETFL, flags) < 0)
	{
		perror("fail to fcntl");
		exit(1);		
	}
	while(1)
	{
		fgets(buf, 32, stdin);

		sleep(1);
		printf("*******************\n");
	}
	return 0;
}
