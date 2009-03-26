// ToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "ToolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CToolsDlg 对话框




CToolsDlg::CToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolsDlg::IDD, pParent)
	, m_strEdit(_T(""))
	, m_bInput(FALSE)
	, m_strEdit2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Check(pDX, IDC_CHECK1, m_bInput);
	DDX_Control(pDX, IDC_BUTTON1, m_btInput);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_COMBOBOXEX2, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_strEdit2);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_PROGRESS1, m_prograss);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_month);
	DDX_Control(pDX, IDC_LIST1, m_list0);
}

BEGIN_MESSAGE_MAP(CToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CToolsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CToolsDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &CToolsDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CToolsDlg::OnBnClickedRadio2)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CToolsDlg::OnHdnItemclickList2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CToolsDlg::OnNMReleasedcaptureSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CToolsDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolsDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CToolsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolsDlg::OnBnClickedButton5)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CToolsDlg::OnMcnSelchangeMonthcalendar1)
END_MESSAGE_MAP()


// CToolsDlg 消息处理程序

BOOL CToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//
	//初始化图标
	m_imgIcon[0]=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_imgIcon[1]=AfxGetApp()->LoadIcon(IDI_ICON2);
	m_imgIcon[2]=AfxGetApp()->LoadIcon(IDI_ICON3);
	m_imgList.Create( 16, 16, ILC_COLOR32 |ILC_MASK ,3, 3 ); //透明图标
	for (int i = 0; i<3; i++)
	{
		m_imgList.Add( m_imgIcon[i] );
	}

	//m_list.SetBkColor(   CLR_NONE   );
	m_list.SetExtendedStyle(LVS_EX_SUBITEMIMAGES);
	m_list.SetImageList(&m_imgList,  LVSIL_SMALL);

	m_list.DeleteAllItems();	
	m_list.InsertColumn(0, CString("游戏名"));
	m_list.InsertColumn(1, CString("公司名"));
	//设置宽度
	CRect r;
	m_list.GetWindowRect(&r);
	int width = (r.right - r.left) / 2 - 10;
	m_list.SetColumnWidth(0, width);
	m_list.SetColumnWidth(1, width);

	//Listcontrol
	LV_ITEM   lvitemAdd ;
	lvitemAdd.mask = LVIF_IMAGE|LVIF_TEXT; 
	lvitemAdd.iItem = 0 ;
	lvitemAdd.iSubItem = 0;
	lvitemAdd.pszText = "完美世界";
	lvitemAdd.iImage = 1;
	m_list.InsertItem(&lvitemAdd);

	lvitemAdd.mask = LVIF_TEXT;
	lvitemAdd.iSubItem = 1;
	lvitemAdd.pszText = "完美时空";
	m_list.SetItem(&lvitemAdd);

	lvitemAdd.mask = LVIF_IMAGE|LVIF_TEXT; 
	lvitemAdd.iItem = 0 ;
	lvitemAdd.iSubItem = 0;
	lvitemAdd.pszText = "星际争霸";
	lvitemAdd.iImage = 0;
	m_list.InsertItem(&lvitemAdd);

	lvitemAdd.mask = LVIF_TEXT;
	lvitemAdd.iSubItem = 1;
	lvitemAdd.pszText = "暴雪";
	m_list.SetItem(&lvitemAdd);

	lvitemAdd.mask = LVIF_IMAGE|LVIF_TEXT; 
	lvitemAdd.iItem = 0 ;
	lvitemAdd.iSubItem = 0;
	lvitemAdd.pszText = "QQ";
	lvitemAdd.iImage = 2;
	m_list.InsertItem(&lvitemAdd);

	lvitemAdd.mask = LVIF_TEXT;
	lvitemAdd.iSubItem = 1;
	lvitemAdd.pszText = "腾讯";
	m_list.SetItem(&lvitemAdd);

	//m_list.InsertItem(0,  "第1行第1列");
	//m_list.SetItemText(0, 1, "第1行第2列");

	//m_list.InsertItem(1,  "第2行第1列");
	//m_list.SetItemText(1, 1, "第2行第2列");

	//Combo Control
	
	m_combo.SetImageList(&m_imgList);
	COMBOBOXEXITEM     cbi;
	CString            str[3] = {"星际争霸","完美世界","QQ"};
	int                nItem;
	for ( int i = 0; i < 3; i++)
	{
		cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
			CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

		cbi.iItem = i;
		//str[i].Format(_T("Item %02d"), i);
		cbi.pszText = (LPTSTR)(LPCTSTR)str[i];
		cbi.cchTextMax = str[i].GetLength();
		cbi.iImage = i;
		cbi.iSelectedImage = 1;
		cbi.iOverlay = 2;
		cbi.iIndent = 1>>2;
		//cbi.iIndent = (i & 0x03);   //Set indentation according
		nItem = m_combo.InsertItem(&cbi);
	}

	/*m_combo.AddString("选项1");
	m_combo.AddString("选项2");
	m_combo.AddString("选项3");*/

	//Slider
	m_slider.SetRange(0, 100);
	m_slider.SetPos(50);
	m_slider.SetTicFreq(10);

	//Prograss
	m_prograss.SetRange(0,100);
	m_prograss.SetStep(1);

	//List
	m_list0.InsertString(0, "列表1");
	m_list0.InsertString(1, "列表2");
	m_list0.InsertString(2, "列表3");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CToolsDlg::OnBnClickedButton1()
{
	m_strEdit = "Hello world";
	UpdateData(FALSE);
}

void CToolsDlg::OnBnClickedButton2()
{
	MessageBox(m_strEdit);
}

void CToolsDlg::OnBnClickedCheck1()
{
	m_bInput = m_bInput? false : true;
	m_btInput.EnableWindow(!m_bInput);
}

void CToolsDlg::OnBnClickedRadio1()
{
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
}

void CToolsDlg::OnBnClickedRadio2()
{
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
}

void CToolsDlg::OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("a");
	*pResult = 0;
}

void CToolsDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	*pResult = 0;
}

void CToolsDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	CString str;
	str.Format("%d", m_slider.GetPos());
	m_strEdit2 = str;
	UpdateData(false);

	*pResult = 0;
}

void CToolsDlg::OnBnClickedButton3()
{
	m_prograss.SetPos(0);

	SetTimer(0,10,NULL);
}



void CToolsDlg::OnBnClickedButton4()
{
	KillTimer(0);
}


void CToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_prograss.StepIt();
	if ( m_prograss.GetPos() == 100)
	{
		KillTimer(0);
		MessageBox("测试结束~");
	}
	CDialog::OnTimer(nIDEvent);
}
void CToolsDlg::OnBnClickedButton5()
{
	COleDateTime data;
	m_month.GetCurSel(data);
	CString str;
	str.Format("%d年%d月%d日", data.GetYear(), data.GetMonth(), data.GetDay());
	MessageBox(str);
}

void CToolsDlg::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
