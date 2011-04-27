#include <iostream>
#import "ComInterface.tlb"
using namespace std;

void main()
{
	HRESULT hr = CoInitialize(NULL);
	ComInterface::IComTestPtr server;
	hr = server.CreateInstance("ComTest.ComServer");
	cout<<server->GetTime()<<endl;
	CoUninitialize();
}