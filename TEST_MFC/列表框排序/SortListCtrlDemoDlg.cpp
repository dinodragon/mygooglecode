// SortListCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SortListCtrlDemo.h"
#include "SortListCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrlDemoDlg dialog

CSortListCtrlDemoDlg::CSortListCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSortListCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSortListCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSortListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSortListCtrlDemoDlg)
	DDX_Control(pDX, IDC_LISTCTRL, m_ctlList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSortListCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSortListCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL, OnClickListctrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrlDemoDlg message handlers

BOOL CSortListCtrlDemoDlg::OnInitDialog()
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
	
	(void)m_ctlList.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_ctlList.SetHeadings(_T("姓名,120;生日,90;得分,50;工资,64") );
	m_ctlList.LoadColumnInfo();

	(void)m_ctlList.AddItem( _T("许世杰"), _T("1960-09-08"), _T("90"), _T("400.5"));
	(void)m_ctlList.AddItem( _T("盛晓玮"), _T("1974-03-12"), _T("89"), _T("70.5"));
	(void)m_ctlList.AddItem( _T("吴玉强"), _T("1970-06-01"), _T("100"), _T("1000.6") );
	//////添加图标//////
	m_HeadIcon.Create(16,16,TRUE,2,2);
	m_HeadIcon.Add(AfxGetApp()->LoadIcon(IDI_HEADICON));
	m_ctlList.SetImageList(&m_HeadIcon,LVSIL_SMALL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSortListCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSortListCtrlDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSortListCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSortListCtrlDemoDlg::OnClickListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_ctlList.GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = m_ctlList.GetNextSelectedItem(pos);
		CString strUserinfo;
		strUserinfo.Format("姓名:%s 生日:%s 得分:%s",m_ctlList.GetItemText(nItem,0),m_ctlList.GetItemText(nItem,1),m_ctlList.GetItemText(nItem,2));
		GetDlgItem(IDC_STATIC1)->SetWindowText(strUserinfo);
	}
	*pResult = 0;
}
