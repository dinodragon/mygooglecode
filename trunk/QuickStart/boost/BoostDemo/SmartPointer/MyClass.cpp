#include "MyClass.h"
#include <iostream>

using namespace std;

MyClass::MyClass(void)
{
  cout<<"construct MyClass!"<<endl;
}

MyClass::~MyClass(void)
{
  cout<<"destruct MyClass!"<<endl;
}

void MyClass::Show(void)
{
  cout<<"This is class MyClass!"<<endl;
}
