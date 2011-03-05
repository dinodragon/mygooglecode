#include <stdio.h>

void main()
{
	char *str1 = malloc(1024*1024*512);
	free(str1);
}