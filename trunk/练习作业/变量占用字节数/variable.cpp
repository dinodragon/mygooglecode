/**************************************************
    显示不同数据类型所占字节

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
using namespace std;

void main()
{
	cout << "bool:" <<sizeof(bool) <<endl;
	cout << "[signed] char:" <<sizeof(char) <<endl;
	cout << "unsigned char:" <<sizeof(unsigned char) <<endl;
	cout << "wchar_t:" <<sizeof(wchar_t) <<endl;
	cout << "[signed] int:" <<sizeof(signed int) <<endl;
	cout << "unsigned [int]:" <<sizeof(unsigned int) <<endl;
	cout << "[signed] short [int]:" <<sizeof(short) <<endl;
	cout << "[signed] long [int]:" <<sizeof(long) <<endl;
	cout << "unsigned short [int]:" <<sizeof(unsigned short) <<endl;
	cout << "unsigned long [int]:" <<sizeof(unsigned long) <<endl;
	cout << "float:" <<sizeof(float) <<endl;
	cout << "double:" <<sizeof(double) <<endl;
	cout << "long double:" <<sizeof(long double) <<endl;
}