#include <iostream>

//һ���ڴ�����������ʾ����
//���¼�http://my.oschina.net/solu/blog/2537

int a = 0; //ȫ�ֳ�ʼ����
char *p1; //ȫ��δ��ʼ����

int main()
{
	int b;// ջ
	char s[] = "abc"; //ջ
	char *p2; //ջ
	char *p3 = "123456"; //"123456\0"�ڳ�������p3��ջ�ϡ�
	static int c =0; //ȫ�֣���̬����ʼ����

	p1 = (char *)malloc(10);
	p2 = (char *)malloc(20);
	//���������10��20�ֽڵ�������ڶ�����

	strcpy(p1, "123456"); //123456\0���ڳ����������������ܻὫ����p3��ָ���"123456"�Ż���һ���ط���
	free(p1);
	free(p2);
	return 0;
}
