#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	
	int i = 0;

	while(1)
	{
	//	getchar();

		printf("+++++++++++++\n");
		sleep(1);
		if(i++ == 5)
		{
			break;
		}
	}

	return 0;
}
