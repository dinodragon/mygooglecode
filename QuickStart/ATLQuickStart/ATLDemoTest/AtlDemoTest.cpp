#include <iostream>
#include "../ATLDemo/ATLDemo_i.h"
#include "../ATLDemo/ATLDemo_i.c"

#import "ATLDemo.dll"
using namespace std;

int main()
{
	//声明HRESULT和Ikuan接口指针 
	IMyCalc * pMyCalc = NULL;
	HRESULT hr = CoInitialize(NULL);    //初始化COM 
	//使用SUCCEEDED宏并检查我们是否能得到一个接口指针
	if(SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_MyCalc,NULL,CLSCTX_INPROC_SERVER,IID_IMyCalc,(void **)&pMyCalc); 
		//如果成功，则调用AddNumbers方法，否则显示相应的出错信息
		if(SUCCEEDED(hr))      
		{
			long ReturnValue; 
			pMyCalc->Add(8,9,&ReturnValue);  
			pMyCalc->Msg();
			cout << "The answer for 8+9 is:" << ReturnValue << endl;
			pMyCalc->Release();
		} 
		else
		{ 
			cout << "CoCreateInstance Failed." << endl; 
		} 
	}   
	CoUninitialize();//释放COM
	return 0;
}