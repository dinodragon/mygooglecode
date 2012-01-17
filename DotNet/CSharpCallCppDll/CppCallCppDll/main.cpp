#include <iostream>

using namespace std;

extern "C" int add(const int x,const int y);
extern "C" int wlen(const wchar_t * str);
extern "C" int len(const char * str);

void main()
{
	cout<<add(2,3)<<endl;
	cout<<wlen(L"abdc")<<endl;
	cout<<len("abdc")<<endl;
}