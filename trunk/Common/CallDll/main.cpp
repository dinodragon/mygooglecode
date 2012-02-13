#include <iostream>

extern "C" __declspec(dllimport) void FuncInDll(void);
extern "C" __declspec(dllimport) void FuncInDll1(void);
__declspec(dllimport) void FuncInDll2(void);
extern "C" __declspec(dllimport) int gl;
extern "C" __declspec(dllimport) int gl1;
__declspec(dllimport) int gl2;
class __declspec(dllimport) CFoo
{
public:
  int fun();
}; 

int main()
{
  FuncInDll();
  FuncInDll1();
  FuncInDll2();
  std::cout<<gl<<std::endl;
  std::cout<<gl1<<std::endl;
  std::cout<<gl2<<std::endl;
  CFoo f;
  std::cout<<f.fun()<<std::endl;
}