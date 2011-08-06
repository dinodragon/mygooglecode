#include <iostream>
#include "../ATLDemo/ATLDemo_i.h"
#include "../ATLDemo/ATLDemo_i.c"

//#import "../ATLDemo/Debug/ATLDemo.dll"
//等效
//#import "progid:ATLDemo.MyCalc.1"  version("1.0")
#import "libid:C440DCEF-9D2D-4970-9410-B597EB6D3AA4" version("1.0")

using namespace std;

void Method1();
void Method2();

int main()
{
	Method1();
	Method2();
	return 0;
}

void Method1()
{
	//需要包含
	//#include "../ATLDemo/ATLDemo_i.h"
	//#include "../ATLDemo/ATLDemo_i.c"
	//声明HRESULT和Ikuan接口指针 
	HRESULT hr = CoInitialize(NULL);    //初始化COM 
	assert(SUCCEEDED(hr));

	IMyCalc * pMyCalc = NULL;
	//使用SUCCEEDED宏并检查我们是否能得到一个接口指针
	hr = CoCreateInstance(CLSID_MyCalc,NULL,CLSCTX_INPROC_SERVER,IID_IMyCalc,(void **)&pMyCalc); 
	assert(SUCCEEDED(hr));

	long ReturnValue; 
	pMyCalc->Add(8,9,&ReturnValue);  
	//pMyCalc->Msg();
	pMyCalc->Echo(::SysAllocString(L"这是使用包含ATL生成的头文件方法调用的。"));
	cout << "The answer for 8+9 is:" << ReturnValue << endl;
	pMyCalc->Release();
	CoUninitialize();//释放COM
}

void Method2()
{
	//导入"../ATLDemo/Debug/ATLDemo.dll"
	HRESULT hr = CoInitialize(NULL);    //初始化COM 
	assert(SUCCEEDED(hr));
	ATLDemoLib::IMyCalcPtr app;
	hr = app.CreateInstance("ATLDemo.MyCalc.1");
	assert(SUCCEEDED(hr));
	//app->Msg();
	hr = app->Echo("这是使用导入类型库的方法调用的。");
	assert(SUCCEEDED(hr));
	app.Release();
	CoUninitialize();//释放COM
}