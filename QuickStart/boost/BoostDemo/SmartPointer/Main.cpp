#include <iostream>
#include "MyClass.h"
#include <boost/shared_ptr.hpp>

void autoPtr();
void shardPtr();
void scopedPtr();
boost::shared_ptr<MyClass> sharedPtr_fun();

int main()
{
  {
    //用shared_ptr传递函数内的指针
    boost::shared_ptr<MyClass> b = sharedPtr_fun();
  }
  autoPtr();
  shardPtr();
  scopedPtr();
}