// Base64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Base64.h"
#include "Base64Dlg.h"
#include <vector>

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


// CBase64Dlg 对话框




CBase64Dlg::CBase64Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBase64Dlg::IDD, pParent)
	, m_source(_T(""))
	, m_base64(_T(""))
	, m_autoconvert(TRUE)
	, m_codepage(0)
	, m_lastOperEncode(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	HKEY hKey;
	DWORD dw;
	RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("Software\\base64"),0,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwAutoConvert;
	DWORD dwCodePage;
	long lReturn=RegQueryValueEx(hKey,TEXT("AutoConvert"),NULL,&dwType,(BYTE *)&dwAutoConvert,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_autoconvert = (BOOL)dwAutoConvert;
	}
	lReturn=RegQueryValueEx(hKey,TEXT("CodePage"),NULL,&dwType,(BYTE *)&dwCodePage,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_codepage = (int)dwCodePage;
		if (m_codepage<0 || m_codepage >2)
		{
			m_codepage = 0;
		}
	}

}

void CBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_SOURCE, m_source);
	//DDV_MaxChars(pDX, m_source, 20000);
	//DDX_Text(pDX, IDC_BASE64, m_base64);
	//DDV_MaxChars(pDX, m_base64, 25000);
	DDX_Check(pDX, IDC_AUTOCONVERT, m_autoconvert);
	DDX_Radio(pDX, IDC_ANSI, m_codepage);
	DDV_MinMaxInt(pDX, m_codepage, 0, 10);
}

BEGIN_MESSAGE_MAP(CBase64Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_BASE64, &CBase64Dlg::OnEnChangeBase64)
	ON_BN_CLICKED(IDC_Help, &CBase64Dlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDC_AUTOCONVERT, &CBase64Dlg::OnBnClickedAutoconvert)
	ON_BN_CLICKED(IDC_ENCODE, &CBase64Dlg::OnBnClickedEncode)
	ON_BN_CLICKED(IDC_DECODE, &CBase64Dlg::OnBnClickedDecode)
	ON_BN_CLICKED(IDC_ANSI, &CBase64Dlg::OnBnClickedAnsi)
	ON_BN_CLICKED(IDC_UTF8, &CBase64Dlg::OnBnClickedUtf8)
	ON_BN_CLICKED(IDC_Unicode, &CBase64Dlg::OnBnClickedUnicode)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DECODETOFILE, &CBase64Dlg::OnBnClickedDecodetofile)
	ON_EN_CHANGE(IDC_SOURCE, &CBase64Dlg::OnEnChangeSource)
END_MESSAGE_MAP()


// CBase64Dlg 消息处理程序

BOOL CBase64Dlg::OnInitDialog()
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
	
	m_rSource = (CRichEditCtrl *)GetDlgItem(IDC_SOURCE);
	ASSERT(m_rSource!=NULL);
	m_rBase64 = (CRichEditCtrl *)GetDlgItem(IDC_BASE64);
	ASSERT(m_rBase64!=NULL);

	m_rSource->SetEventMask(m_rSource->GetEventMask() | ENM_CHANGE);
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() | ENM_CHANGE);

	CButton * decode = (CButton *)GetDlgItem(IDC_DECODE);
	ASSERT(decode!=NULL);
	decode->EnableWindow(!m_autoconvert);
	CButton * encode = (CButton *)GetDlgItem(IDC_ENCODE);
	ASSERT(encode!=NULL);
	encode->EnableWindow(!m_autoconvert);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBase64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBase64Dlg::OnPaint()
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
HCURSOR CBase64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBase64Dlg::OnEnChangeBase64()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_autoconvert)
	{
		Decode();
	}
}


void CBase64Dlg::OnEnChangeSource()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_autoconvert)
	{
		Encode();
	}
}


void CBase64Dlg::OnBnClickedHelp()
{
	ShellExecute(NULL,TEXT("open"),TEXT("http://www.yangfei.org/post/base64.html?from=base64v1.5"),NULL,NULL,SW_SHOWNORMAL);
}

void CBase64Dlg::OnBnClickedAutoconvert()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CButton * decode = (CButton *)GetDlgItem(IDC_DECODE);
	ASSERT(decode!=NULL);
	decode->EnableWindow(!m_autoconvert);
	CButton * encode = (CButton *)GetDlgItem(IDC_ENCODE);
	ASSERT(encode!=NULL);
	encode->EnableWindow(!m_autoconvert);
}

//将原码进行加密
void CBase64Dlg::Encode(void)
{
	//UpdateData();
	GetDlgItemTextA(IDC_SOURCE,m_source);
	m_lastOperEncode = TRUE;
 	const char * sourceAnsi = m_source.GetBuffer();
	if (m_codepage == 0) //ANSI
	{
		m_base64 = CString(base64.encode(sourceAnsi,strlen(sourceAnsi)).c_str());
	} 
	else if(m_codepage == 1) //UTF-8
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, sourceUnich, dwUnicodeNum);

		DWORD dwUTF8Num = WideCharToMultiByte (CP_UTF8, 0, sourceUnich, -1, NULL, 0,NULL,NULL);
		CHAR * souceUTF8Char = new CHAR[dwUTF8Num];
		WideCharToMultiByte (CP_UTF8, 0, sourceUnich, -1, souceUTF8Char, dwUTF8Num,NULL,NULL);
		
		m_base64 = CString(base64.encode(souceUTF8Char,strlen(souceUTF8Char)).c_str());
		delete[] sourceUnich;
		delete[] souceUTF8Char;
	}
	else if (m_codepage == 2) //Unicode
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, sourceUnich, dwUnicodeNum);
		CHAR * sourceWchToChar = new CHAR[dwUnicodeNum<<1];
		for (DWORD i = 0 ;i<dwUnicodeNum;i++)
		{
			sourceWchToChar[i<<1] = (sourceUnich[i] >>8 );
			sourceWchToChar[(i<<1) + 1] = sourceUnich[i] & 0x00FF;
		}
		m_base64 = CString(base64.encode(sourceWchToChar,(dwUnicodeNum-1)<<1).c_str());
		delete[] sourceUnich;
		delete[] sourceWchToChar;
	}
	m_source.ReleaseBuffer();
	//UpdateData(FALSE);
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() ^ ENM_CHANGE);
	SetDlgItemText(IDC_BASE64,m_base64.GetBuffer());
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() | ENM_CHANGE);
	m_base64.ReleaseBuffer();
}

//解密
void CBase64Dlg::Decode(void)
{
	GetDlgItemTextA(IDC_BASE64,m_base64);
	m_lastOperEncode = FALSE;
	std::vector<char> sourceChars = base64.decode(std::string(m_base64));

	size_t sourceLen = sourceChars.size();
	char * sourceByte = new char[sourceLen+1];
	for (size_t i = 0;i<sourceLen ;i++ )
	{
		sourceByte[i] = sourceChars[i];
	}
	sourceByte[sourceLen] = 0;
	if (m_codepage == 0) //ANSI
	{
		m_source = CString(sourceByte);
	} 
	else if(m_codepage == 1) //UTF-8
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_UTF8, 0, sourceByte, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_UTF8, 0, sourceByte, -1, sourceUnich, dwUnicodeNum);

		DWORD dwANSICharNum = WideCharToMultiByte (CP_ACP, 0, sourceUnich, -1, NULL, 0,NULL,NULL);
		CHAR * souceANSIChar = new CHAR[dwANSICharNum];
		WideCharToMultiByte (CP_ACP, 0, sourceUnich, -1, souceANSIChar, dwANSICharNum,NULL,NULL);

		m_source = CString(souceANSIChar);
		delete[] sourceUnich;
		delete[] souceANSIChar;
	}
	else if (m_codepage == 2) //Unicode
	{
		WCHAR * WideChar = new WCHAR[sourceLen/2 + 1];
		for (DWORD i = 0 ;i<sourceLen/2;i++)
		{
			WideChar[i] = ((sourceByte[i<<1])<<8) | (sourceByte[(i<<1) + 1]&0x00FF) ;
		}
		WideChar[sourceLen/2] = 0;

		DWORD dwANSICharNum = WideCharToMultiByte (CP_ACP, 0, WideChar, -1, NULL, 0,NULL,NULL);
		CHAR * souceANSIChar = new CHAR[dwANSICharNum];
		WideCharToMultiByte (CP_ACP, 0, WideChar, -1, souceANSIChar, dwANSICharNum,NULL,NULL);

		m_source = CString(souceANSIChar);
		delete[] WideChar;
		delete[] souceANSIChar;
	}
	delete[] sourceByte;
	m_rSource->SetEventMask(m_rSource->GetEventMask() ^ ENM_CHANGE);
	SetDlgItemText(IDC_SOURCE,m_source.GetBuffer());
	m_source.ReleaseBuffer();
	m_rSource->SetEventMask(m_rSource->GetEventMask() | ENM_CHANGE);
}

void CBase64Dlg::OnBnClickedEncode()
{
	// TODO: 在此添加控件通知处理程序代码
	Encode();
}

void CBase64Dlg::OnBnClickedDecode()
{
	// TODO: 在此添加控件通知处理程序代码
	Decode();
}

void CBase64Dlg::OnBnClickedAnsi()
{
	// TODO: 在此添加控件通知处理程序代码
	m_codepage = 0;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
	
}

void CBase64Dlg::OnBnClickedUtf8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_codepage = 1;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
}

void CBase64Dlg::OnBnClickedUnicode()
{
	// TODO: 在此添加控件通知处理程序代码
	m_codepage = 2;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
}

void CBase64Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HKEY hKey;
	DWORD dw;
	RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("Software\\base64"),0,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
	long lReturn=RegSetValueEx(hKey,TEXT("AutoConvert"),0L,REG_DWORD,(const BYTE *) &m_autoconvert,sizeof(DWORD));
	RegSetValueEx(hKey,TEXT("CodePage"),0L,REG_DWORD,(const BYTE *) &m_codepage,sizeof(DWORD));
	CDialog::OnClose();
}

void CBase64Dlg::OnBnClickedDecodetofile()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemTextA(IDC_BASE64,m_base64);
	char szFilters[]=
		"All Files (*.*)|*.*|";
	CFileDialog fileDlg(FALSE,"txt",NULL,OFN_HIDEREADONLY,szFilters);
	if( fileDlg.DoModal ()==IDOK )
	{
		std::vector<char> sourceChars = base64.decode(std::string(m_base64));
		size_t sourceLen = sourceChars.size();
		char * sourceByte = new char[sourceLen];
		for (size_t i = 0;i<sourceLen ;i++ )
		{
			sourceByte[i] = sourceChars[i];
		}
		CString pathName = fileDlg.GetPathName();
		CFile file(pathName,CFile::modeCreate | CFile::modeWrite);
		file.Write(sourceByte,(UINT)sourceLen);
		file.Close();
		delete[] sourceByte;
	}

}

