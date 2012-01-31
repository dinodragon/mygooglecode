#include <iostream>

class A2
{
public:
  virtual void fun(){}
  int a;
  int b;
};

class A
{
public:
  virtual void fun(){}
  int a;
  int b;
};

class B:public A
{
public:
  virtual void fun(){}
  virtual void fun2(){}
  int c;
};

class C:public B,public A2
{
public:
  int d;
};

void vfptrtest()
{
  //详见《深入探索C++对象模型》P130
  //输出成员a的相对偏移量
  printf("&A::a:%p\r\n",&B::a);
  //std::cout<<&A::a<<std::endl; 这样不行，数据类型不同
  printf("&A::b:%p\r\n",&B::b);
  printf("&A::b:%p\r\n",&B::c);
  B b;
  C c;
}