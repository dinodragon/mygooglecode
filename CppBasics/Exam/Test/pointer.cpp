#include <stdio.h>
#include <string.h>

static int x;

void PointerTest()
{
	char c=128; 
	printf("c=%d\r\n",c); //�����-128
	//c��0x10,�������int�����λΪ1���Ǹ�������������ֵ����0x00�Ĳ������128�����������128��

	char aa[10];
	printf("%d\r\n",strlen(aa));

	printf("��̬ȫ�ֱ���x=%d\r\n",x);

}