#include <iostream>
#include "../ATLDemo/ATLDemo_i.h"
#include "../ATLDemo/ATLDemo_i.c"

#import "../ATLDemo/Debug/ATLDemo.dll"
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
	IMyCalc * pMyCalc = NULL;
	HRESULT hr = CoInitialize(NULL);    //��ʼ��COM 
	//ʹ��SUCCEEDED�겢��������Ƿ��ܵõ�һ���ӿ�ָ��
	if(SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_MyCalc,NULL,CLSCTX_INPROC_SERVER,IID_IMyCalc,(void **)&pMyCalc); 
		//����ɹ��������AddNumbers������������ʾ��Ӧ�ĳ�����Ϣ
		if(SUCCEEDED(hr))      
		{
			long ReturnValue; 
			pMyCalc->Add(8,9,&ReturnValue);  
			//pMyCalc->Msg();
			pMyCalc->Echo(::SysAllocString(L"����ʹ�ð���ATL���ɵ�ͷ�ļ��������õġ�"));
			cout << "The answer for 8+9 is:" << ReturnValue << endl;
			pMyCalc->Release();
		} 
		else
		{ 
			cout << "CoCreateInstance Failed." << endl; 
		} 
	}   
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
	app->Echo("����ʹ�õ������Ϳ�ķ������õġ�");
	app.Release();
	CoUninitialize();//�ͷ�COM
}