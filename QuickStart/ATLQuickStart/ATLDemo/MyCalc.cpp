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
