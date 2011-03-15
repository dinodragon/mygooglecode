#include <iostream>
#include "../ATLDemo/ATLDemo_i.h"
#include "../ATLDemo/ATLDemo_i.c"

#import "ATLDemo.dll"
using namespace std;

int main()
{
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
			pMyCalc->Msg();
			cout << "The answer for 8+9 is:" << ReturnValue << endl;
			pMyCalc->Release();
		} 
		else
		{ 
			cout << "CoCreateInstance Failed." << endl; 
		} 
	}   
	CoUninitialize();//�ͷ�COM
	return 0;
}