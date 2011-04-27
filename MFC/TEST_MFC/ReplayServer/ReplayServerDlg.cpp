// ReplayServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReplayServer.h"
#include "ReplayServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReplayServerDlg �Ի���




CReplayServerDlg::CReplayServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplayServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReplayServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReplayServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CRATE, &CReplayServerDlg::OnBnClickedCrate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CReplayServerDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CReplayServerDlg ��Ϣ�������

BOOL CReplayServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	SetTimer(2,600000,NULL); //��10���������ϵ�����,��ֹ���ӵ�����˿ڲ��Ͽ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReplayServerDlg::OnPaint()
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
HCURSOR CReplayServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReplayServerDlg::OnBnClickedCrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnTimer(1);
	SetTimer(1,60000,NULL);
}

void CReplayServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(nIDEvent==1 && m_mySocket.m_bConnected == TRUE) return;
	if(nIDEvent==2)
	{
		m_mySocket.Close();
		Sleep(100);
		return;
	}
	CTime time; 
	time=::CTime::GetCurrentTime(); 
	CString str; 
	str=time.Format("%H:%M:%S"); 
	
	AddMessage(str + _T("��������..."));

	m_mySocket.Close();
	Sleep(100);
	m_mySocket.Create();
	m_mySocket.Connect(CString(_T("localhost")).GetBuffer(),9592);

	CDialog::OnTimer(nIDEvent);
}

void CReplayServerDlg::AddMessage(CString str)
{
	CString temp;
	GetDlgItemText(IDC_RICHEDIT21,temp);
	if( -1==str.Find(_T("\r")) && -1==str.Find(_T("\n")))
		str += _T("\n");
	temp += str;
	SetDlgItemText(IDC_RICHEDIT21,temp);

	CRichEditCtrl * m_RichEditCtrl = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT21);
	m_RichEditCtrl->LineScroll(2,1);
}

void CReplayServerDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	AddMessage(_T("ֹͣ����"));
}
