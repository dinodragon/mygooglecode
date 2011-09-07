#pragma once
#include <iostream>
//#pragma once 与头文件卫士功能相当，但头文件卫士跨平台能力更强。
using namespace std;
class CMath
{
public:
	CMath(void);
	~CMath(void);
	int Add(int a, int b);
};
