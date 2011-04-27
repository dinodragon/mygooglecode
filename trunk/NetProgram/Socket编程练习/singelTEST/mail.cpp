#include <iostream>
#include <windows.h>

using namespace std;

long TStringToLong(const wstring& strIn)
   {
      TCHAR* pStopString = 0;
      return wcstol(&*strIn.begin(), &pStopString, 10);
   }

void fun(const int & x)
{
	cout<<x<<endl;
}

void main()
{
	wstring bb = TEXT("1234");
	long aa = TStringToLong(TEXT("1234"));
	cout<<aa+1<<endl;
	fun(23);
}


