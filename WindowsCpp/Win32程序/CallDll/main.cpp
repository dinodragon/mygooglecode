#include <iostream>
#include <windows.h>

using namespace std;


/*_declspec(dllimport) int add(int a, int b);
_declspec(dllimport) int sub(int a, int b);
*/

void main()
{
	HINSTANCE hins;
	hins = LoadLibrary(TEXT("dll1.dll"));
	typedef int (*Addproc )(int ,int);
	//cout<<add(5,3)<<endl;
	Addproc addp = (Addproc)GetProcAddress(hins,"add");
	cout<<addp(5,3)<<endl;
}