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

class D:C,AA
{

};

void main()
{
	
}