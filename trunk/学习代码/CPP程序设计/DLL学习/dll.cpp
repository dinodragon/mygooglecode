#include <objbase.h>
#include <iostream>

using namespace std;

extern "C" __declspec(dllexport) void FuncInDll (void)
{
    cout<<"FuncInDll is called!"<<endl;
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 

{
    return true;
}

