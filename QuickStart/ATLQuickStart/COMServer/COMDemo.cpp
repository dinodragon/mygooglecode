// COMDemo.cpp : Implementation of CCOMDemo

#include "stdafx.h"
#include "COMDemo.h"


// CCOMDemo


STDMETHODIMP CCOMDemo::Greeting(BSTR name, BSTR* message)
{
	// TODO: Add your implementation code here
	CComBSTR tmp("Welcom, ");
	tmp.Append(name);
	*message = tmp;
	return S_OK;
}
