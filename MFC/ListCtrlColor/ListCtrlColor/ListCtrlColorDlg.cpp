// ListCtrlColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlColor.h"
#include "ListCtrlColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CListCtrlColorDlg dialog




CListCtrlColorDlg::CListCtrlColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlColorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlColorDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST1, m_lstBooks);
}

BEGIN_MESSAGE_MAP(CListCtrlColorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CListCtrlColorDlg message handlers

BOOL CListCtrlColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

  // Insert the columns
	m_lstBooks.InsertColumn(0, _T("Author"));
	m_lstBooks.InsertColumn(1, _T("Book"));

  // Define the data
	static struct 
	{
	  TCHAR m_szAuthor[50];
	  TCHAR m_szTitle[100];
	} BOOK_INFO[] = {
	_T("Tom Archer"), _T("Visual C++.NET Bible"),
	_T("Tom Archer"), _T("Extending MFC Applications with the .NET Framework"),
	_T("Brian Johnson"), _T("XBox 360 For Dummies")
	};

  // Insert the data
  int idx;
  for (int i = 0; i < sizeof BOOK_INFO / sizeof BOOK_INFO[0]; i++)
  {
    idx = m_lstBooks.InsertItem(i, BOOK_INFO[i].m_szAuthor);
    m_lstBooks.SetItemText(i, 1, BOOK_INFO[i].m_szTitle);
  }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlColorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListCtrlColorDlg::OnPaint()
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
HCURSOR CListCtrlColorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

