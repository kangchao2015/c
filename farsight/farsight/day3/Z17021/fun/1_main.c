#include <stdio.h>

int main(int argc, const char *argv[])
{
	//char *argv[];   						//本质：数组，元素是char *指针
	printf("argc    = %d\n",argc); 			//命令行的参数个数
	printf("argv[1] = %s\n",argv[1]);  		//命令行字符串参数的首地址
	printf("argv[0] = %c\n",*(argv[0]+1)); 

//	printf("argv[0] = %s\n","hello"); 

	
	return 0;
}
