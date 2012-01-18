#include "MyClass.h"
#include <iostream>

MyClass::MyClass(void)
{
  std::cout<<"MyClass construct!"<<std::endl;
}

MyClass::~MyClass(void)
{
  std::cout<<"MyClass deconstruct!"<<std::endl;
}
