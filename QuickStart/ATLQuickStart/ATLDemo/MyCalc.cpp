// MyCalc.cpp : CMyCalc 的实现

#include "stdafx.h"
#include "MyCalc.h"


// CMyCalc


STDMETHODIMP CMyCalc::Add(LONG a, LONG b, LONG* result)
{
	// TODO: 在此添加实现代码
	*result = a + b;
	return S_OK;
}

STDMETHODIMP CMyCalc::Msg()
{
	MessageBox(NULL,TEXT("这是来自Com组件的消息"),TEXT("标题"),MB_OK);
	return S_OK;
}

STDMETHODIMP CMyCalc::Msg2(void)
{
	// TODO: Add your implementation code here
	MessageBox(NULL,TEXT("这是来自Com组件Msg2的消息"),TEXT("标题"),MB_OK);
	return S_OK;
}
