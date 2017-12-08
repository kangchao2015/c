//指针函数：本质是函数，返回值是指针

#include <stdio.h>
#include <string.h>

char * my_strcpy(char *a, char *b)
{
	char *temp = a;

	while(*b != '\0')
	{
		*a = *b;
		a++;
		b++;
	}
	*a = '\0';
	return temp;
}


int main(int argc, const char *argv[])
{
	char a[10] = "world"; 			
	char b[] = "bei";
	printf("a = %s\n",a); 
	printf("a = %s\n", my_strcpy(a,b));

#if 0
	printf("a = %s\n", strcpy(a,"abc"));
//	w  o  r  l  d  \0
//	b  e  i  \0
#endif

	return 0;
}


