// MyCalc.cpp : CMyCalc ��ʵ��

#include "stdafx.h"
#include "MyCalc.h"


// CMyCalc


STDMETHODIMP CMyCalc::Add(LONG a, LONG b, LONG* result)
{
	// TODO: �ڴ����ʵ�ִ���
	*result = a + b;
	return S_OK;
}

STDMETHODIMP CMyCalc::Msg()
{
	MessageBox(NULL,TEXT("��������Com�������Ϣ"),TEXT("����"),MB_OK);
	return S_OK;
}

STDMETHODIMP CMyCalc::Msg2(void)
{
	// TODO: Add your implementation code here
	MessageBox(NULL,TEXT("��������Com���Msg2����Ϣ"),TEXT("����"),MB_OK);
	return S_OK;
}
