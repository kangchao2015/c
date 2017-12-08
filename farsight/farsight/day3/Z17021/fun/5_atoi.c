#include <stdio.h>
#include <stdlib.h>

int my_atoi(char *a)
{
	int sum = 0;
	while('0' <= *a && *a <= '9')   
	{ 
		sum = sum *10 + (*a - '0');
		a++;
	}

	return sum;
}

int main(int argc, const char *argv[])
{
	char a[] = "123a4";
	printf("a = %s\n",a);
//	printf("a = %d\n",atoi(a)); 	//将数值形式的字符串，转化成整数
	printf("a = %d\n",my_atoi(a)); 

	return 0;
}
