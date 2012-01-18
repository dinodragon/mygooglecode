#include <iostream>

class Base
{
public:
  int x;
  int y;
  Base():x(1),y(2)
  {}
  void fun()
  {
    std::cout<<"this is base!"<<std::endl;
  }
};

class Derived:public Base
{
public:
  int z;
  Derived():z(3)
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