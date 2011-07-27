#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "reverse.h"
#include "myatoi.h"

//随意写的几个题目，关于人民搜索笔试题
int main()
{
	const char a[] = "1234457";
	int i = atoi(a);
	int b = myatoi(a);
	assert(i == b);
	printf("%d %d\r\n",i,b);
	char source[] = "hello world!";
	char des[80];
	reverse(source,des);
	printf("%s\r\n",des);
	return 0;
}
