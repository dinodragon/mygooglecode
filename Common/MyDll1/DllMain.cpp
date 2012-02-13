#include <iostream>
#include <Windows.h>  //用于DllMain的相关数据类型

//导出函数
extern "C" __declspec(dllexport) void FuncInDll(void);
void FuncInDll(void)
{
  std::cout<<"funcInDll"<<std::endl;
}
//声明与定义可以分开，也可以写到一起
extern "C" __declspec(dllexport) void FuncInDll1(void)
{
  std::cout<<"funcInDll1"<<std::endl;
}
//“extern “C”是可选的，没有时导出的名称是修改过的
__declspec(dllexport) void FuncInDll2(void);
void FuncInDll2(void)
{
  std::cout<<"funcInDll2"<<std::endl;
}

//导出变量
extern "C" __declspec(dllexport) int gl;
int gl = 10;
//声明与定义可以分开，也可以写到一起
extern "C" __declspec(dllexport) int gl1 = 11;
//“extern “C”是可选的，没有时导出的名称是修改过的
__declspec(dllexport) int gl2 = 12;

//导出类，不能加“extern “C”
class __declspec(dllexport) CFoo
{
public:
  int fun()
  {
    return 5;
  }
}; 
//导出情况可以使用dependency walker查看
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}