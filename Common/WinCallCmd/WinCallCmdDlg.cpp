// WinCallCmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinCallCmd.h"
#include "WinCallCmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinCallCmdDlg dialog




CWinCallCmdDlg::CWinCallCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinCallCmdDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinCallCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinCallCmdDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDOK, &CWinCallCmdDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDC_BUTTON1, &CWinCallCmdDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWinCallCmdDlg message handlers

BOOL CWinCallCmdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinCallCmdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinCallCmdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void fun()
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );
  TCHAR cmdline[80] = TEXT("dir");
  // Start the child process. 
  if( !CreateProcess(NULL,   // No module name (use command line). 
    cmdline, // Command line. 
    NULL,             // Process handle not inheritable. 
    NULL,             // Thread handle not inheritable. 
    FALSE,            // Set handle inheritance to FALSE. 
    0,                // No creation flags. 
    NULL,             // Use parent's environment block. 
    NULL,             // Use parent's starting directory. 
    &si,              // Pointer to STARTUPINFO structure.
    &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
  {
    printf( "CreateProcess failed (%d).\n", GetLastError() );
    return;
  }
  // Wait until child process exits.
  //WaitForSingleObject( pi.hProcess, INFINITE );
  // Close process and thread handles. 
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );
  return;
}

void CWinCallCmdDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here

  OnOK();
}

void CWinCallCmdDlg::OnBnClickedButton1()
{
  // TODO: Add your control notification handler code here
  fun();
}
