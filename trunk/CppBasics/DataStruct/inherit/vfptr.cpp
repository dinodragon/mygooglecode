#include <iostream>

class A
{
public:
  //virtual void fun(){}
  int a;
  int b;
};

void vfptrtest()
{
  //详见《深入探索C++对象模型》P130
  //输出成员a的相对偏移量
  printf("&A::a:%p\r\n",&A::a);
  //std::cout<<&A::a<<std::endl; 这样不行，数据类型不同
  printf("&A::b:%p\r\n",&A::b);
  //std::cout<<&A::b<<std::endl;
}