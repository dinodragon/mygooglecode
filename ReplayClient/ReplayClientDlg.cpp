// ReplayClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReplayClient.h"
#include "ReplayClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReplayClientDlg �Ի���




CReplayClientDlg::CReplayClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplayClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReplayClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReplayClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, &CReplayClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_LISTENING, &CReplayClientDlg::OnBnClickedListening)
END_MESSAGE_MAP()


// CReplayClientDlg ��Ϣ�������

BOOL CReplayClientDlg::OnInitDialog()
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

void CReplayClientDlg::OnPaint()
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
HCURSOR CReplayClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReplayClientDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	TCHAR buf[200];
	GetDlgItemText(IDC_SENDEDIT,buf,200);
	m_mySocket.m_Socket.Send(buf,sizeof(buf));
}

void CReplayClientDlg::OnBnClickedListening()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mySocket.Create(9592);
	m_mySocket.Listen();
}
