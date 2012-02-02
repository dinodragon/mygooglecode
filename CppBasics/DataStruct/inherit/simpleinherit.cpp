#include <iostream>

class A
{
public:
  int x;
  A(int x = 0):x(0)
  {

  }
};
class Base
{
public:
  int x;
  int y;
  Base(/*int x*/):x(1),y(2)
  {}
  void fun()
  {
    std::cout<<"this is base!"<<std::endl;
  }
};

class Derived:public Base
{
public:
  //基类需要提供默认构造函数,或在初始化列表中明确调用
  A a; //class A需要提供默认的构造函数，或在初始化列表中明确调用
  int z;
  Derived():z(3)/*,Base(0)*/
  {}
  void fun()
  {
    std::cout<<"this is derived!"<<std::endl;
  }
};

void fun(Base b)
{
  b.fun();
}

void simpleinherit()
{
  Derived derived;
  fun(derived);
  Base b = derived;
  b.x = 4;
  //此时derived.x值不变。说明b和derived是不同的两个对象。
  Base *pb = &derived;
  pb->x = 4;
  //此时derived.x == 4,说明pb和derived指向同一内存空间
}