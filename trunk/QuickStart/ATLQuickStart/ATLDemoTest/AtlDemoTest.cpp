#include <iostream>
#include "../ATLDemo/ATLDemo_i.h"
#include "../ATLDemo/ATLDemo_i.c"

//#import "../ATLDemo/Debug/ATLDemo.dll"
//��Ч
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
	//��Ҫ����
	//#include "../ATLDemo/ATLDemo_i.h"
	//#include "../ATLDemo/ATLDemo_i.c"
	//����HRESULT��Ikuan�ӿ�ָ�� 
	HRESULT hr = CoInitialize(NULL);    //��ʼ��COM 
	assert(SUCCEEDED(hr));

	IMyCalc * pMyCalc = NULL;
	//ʹ��SUCCEEDED�겢��������Ƿ��ܵõ�һ���ӿ�ָ��
	hr = CoCreateInstance(CLSID_MyCalc,NULL,CLSCTX_INPROC_SERVER,IID_IMyCalc,(void **)&pMyCalc); 
	assert(SUCCEEDED(hr));

	long ReturnValue; 
	pMyCalc->Add(8,9,&ReturnValue);  
	//pMyCalc->Msg();
	pMyCalc->Echo(::SysAllocString(L"����ʹ�ð���ATL���ɵ�ͷ�ļ��������õġ�"));
	cout << "The answer for 8+9 is:" << ReturnValue << endl;
	pMyCalc->Release();
	CoUninitialize();//�ͷ�COM
}

void Method2()
{
	//����"../ATLDemo/Debug/ATLDemo.dll"
	HRESULT hr = CoInitialize(NULL);    //��ʼ��COM 
	assert(SUCCEEDED(hr));
	ATLDemoLib::IMyCalcPtr app;
	hr = app.CreateInstance("ATLDemo.MyCalc.1");
	assert(SUCCEEDED(hr));
	//app->Msg();
	hr = app->Echo("����ʹ�õ������Ϳ�ķ������õġ�");
	assert(SUCCEEDED(hr));
	app.Release();
	CoUninitialize();//�ͷ�COM
}