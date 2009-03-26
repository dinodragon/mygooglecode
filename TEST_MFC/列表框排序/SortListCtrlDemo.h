// SortListCtrlDemo.h : main header file for the SORTLISTCTRLDEMO application
//

#if !defined(AFX_SORTLISTCTRLDEMO_H__ACA3FA05_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
#define AFX_SORTLISTCTRLDEMO_H__ACA3FA05_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrlDemoApp:
// See SortListCtrlDemo.cpp for the implementation of this class
//

class CSortListCtrlDemoApp : public CWinApp
{
public:
	CSortListCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSortListCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SORTLISTCTRLDEMO_H__ACA3FA05_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
