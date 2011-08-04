// FtpDownLoaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FtpDownLoader.h"
#include "FtpDownLoaderDlg.h"
#include "afxinet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFtpDownLoaderDlg �Ի���




CFtpDownLoaderDlg::CFtpDownLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtpDownLoaderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDownLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFtpDownLoaderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFtpDownLoaderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFtpDownLoaderDlg ��Ϣ�������

BOOL CFtpDownLoaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFtpDownLoaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CFtpDownLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFtpDownLoaderDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::auto_ptr<CInternetSession> m_pInetSession(new CInternetSession);   
	std::auto_ptr<CFtpConnection> m_pFtpConnection(m_pInetSession->GetFtpConnection(TEXT("localhost"),TEXT("anonymous"),TEXT("a@a.a"),21,FALSE));

	if(m_pFtpConnection->GetFile(TEXT("/1/1.t"),TEXT("f:\\1.t"),FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY,1))
	{   
		AfxMessageBox(TEXT("���سɹ���"));
	}
	if(m_pFtpConnection->GetFile(TEXT("/1/1.t"),TEXT("f:\\2.t"),FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY,1))
	{   
		AfxMessageBox(TEXT("���سɹ���"));
	}
	//��command��ʽ��ȡ�ļ���С	TCHAR databuf[256];  	DWORD size=256;   	BOOL bRes;	DWORD dwError;
	m_pFtpConnection->Command(_T("SIZE /1/1.t \r\n"),CFtpConnection::CmdRespNone); 	bRes =InternetGetLastResponseInfo(&dwError,databuf,&size);  


	//CInternetFile * a = m_pFtpConnection->OpenFile(TEXT("/1.t")); 
	//ULONGLONG fileSize = a->GetLength();
	//a->Close();
	CString str;
	m_pFtpConnection->GetCurrentDirectory(str);
	m_pInetSession->Close();
	m_pFtpConnection->Close();
	//OnOK();
}
