#include <stdio.h>
#include <string.h>

static int x;

void PointerTest()
{
	char c=128; 
	printf("c=%d\r\n",c); //会输出-128
	//c＝0x10,输出的是int，最高位为1，是负数，所以它的值就是0x00的补码就是128，所以输出－128。

	char aa[10];
	printf("%d\r\n",strlen(aa));

	printf("静态全局变量x=%d\r\n",x);

}