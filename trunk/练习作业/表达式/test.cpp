/**************************************************
    ����һЩ�򵥵Ĳ���

                 ������ƣ����
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <windows.h>

using namespace std;

void main()
{
/*
//�������������������������ֵ
	int a=32,b=65;
	a=( a = a + b , b = a - b , a - b );
	cout<<"a="<<a<<",b="<<b<<endl;

//��������ʽ
	cout << sizeof(unsigned int) <<endl;
*/
/*
	wchar_t a[]=L"abc";
	wchar_t * p = a;
	cout<<a<<endl<<wcslen(a)<<endl;
*/

	typedef struct {
		int i;
		int b;
		char a;
		char c;
	} H;
	int i=2;		
	char szBuffer[100] ;
	sprintf_s(szBuffer,100,"The sum of %i and %i is %i", 5, 3, 5+3);
	puts(szBuffer);
	sprintf_s(szBuffer,100,"The sum of %i and %i is %i", 5, 3, 5+3) ;
	puts(szBuffer);
	cout<<sizeof(HINSTANCE__)<<endl;
	HINSTANCE__ dd = {12};
	cout<<dd<<endl;
	H a={3,4,'a','b'};
	void *p = &a;
	cout<<sizeof(H)<<endl;
}