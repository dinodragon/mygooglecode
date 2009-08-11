// ActiveXClock.cpp : CActiveXClockApp �� DLL ע���ʵ�֡�

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



// CActiveXClockApp::InitInstance - DLL ��ʼ��

BOOL CActiveXClockApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CActiveXClockApp::ExitInstance - DLL ��ֹ

int CActiveXClockApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
