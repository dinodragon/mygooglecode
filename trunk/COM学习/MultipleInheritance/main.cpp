#include <iostream>

using namespace std;

class A
{

};

class B:public A
{

};

class C:public B
{

};

class AA:B
{

};

//多继承的多个基类中，他们不能已经有继承关系。
class D:C,AA
{

};

void main()
{

}