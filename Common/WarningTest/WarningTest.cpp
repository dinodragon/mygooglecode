#include <iostream>
//该头文件中会产生一个4244警告
#include "WarningTest.h"
using namespace std;

#pragma warning(push)   //是保存当前的编译器警告状态；
#pragma warning(disable:4244)

void main()
{
	double x = 0.0;
	int y;
	y = x; //编译时这里会有个警告，但被禁用了。只剩下了头文件里的警告，warning C4244: '=' :conversion from 'double' to 'int', possible loss of data
	cout<<y<<endl;
}
#pragma warning(pop)   //是恢复原先的警告状态。   

