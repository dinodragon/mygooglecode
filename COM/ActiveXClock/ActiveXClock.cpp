// ActiveXClock.cpp : CActiveXClockApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "ActiveXClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CActiveXClockApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xF6D71A34, 0xEEF1, 0x4693, { 0x96, 0x8, 0x79, 0xA3, 0xB6, 0xE8, 0x8F, 0x4 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CActiveXClockApp::InitInstance - DLL 初始化

BOOL CActiveXClockApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CActiveXClockApp::ExitInstance - DLL 终止

int CActiveXClockApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
