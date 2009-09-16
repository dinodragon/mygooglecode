#include <iostream>

using namespace std;

#pragma pack(push) //保存对齐状态

//详细内容参考http://www.cnblogs.com/bingxuefly/archive/2007/11/12/957056.html

//#pragma pack(4)//设定为4字节对齐，默认值
#pragma pack(1)//设定为1字节对齐，下面的输出就会变成13

struct MyStruct
{
	double dda1; //8字节
	char dda; //1字节
	int type; //4字节
};

void main()
{
	cout<<"sizeof(MyStruct):"<<sizeof(MyStruct)<<endl; //输出16
}

#pragma pack(pop)//恢复对齐状态