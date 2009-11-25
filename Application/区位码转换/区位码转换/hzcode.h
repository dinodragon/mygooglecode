// hzcode.h : main header file for the HZCODE application
//

#if !defined(AFX_HZCODE_H__541A5635_0ED5_49C8_BF31_90F0169E9145__INCLUDED_)
#define AFX_HZCODE_H__541A5635_0ED5_49C8_BF31_90F0169E9145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHzcodeApp:
// See hzcode.cpp for the implementation of this class
//

class CHzcodeApp : public CWinApp
{
public:
	CHzcodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHzcodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHzcodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HZCODE_H__541A5635_0ED5_49C8_BF31_90F0169E9145__INCLUDED_)
