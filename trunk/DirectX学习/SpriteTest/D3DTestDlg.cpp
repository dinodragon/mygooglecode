// D3DTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "D3DTest.h"
#include "D3DTestDlg.h"
#include <d3d9.h>
#include <d3dx9.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


struct CUSTOMVERTEX
{
	float x, y, z; //��������
	DWORD color; //������ɫ
};
//����FVF�õ������������ ��ɫ
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// CD3DTestDlg �Ի���

CD3DTestDlg::CD3DTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CD3DTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bMoveAble = TRUE;
}

void CD3DTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD3DTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CD3DTestDlg ��Ϣ�������

BOOL CD3DTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	InitD3D(); //D3D��ʼ��
	InitGeometry(); //���н�ģ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CD3DTestDlg::OnPaint()
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
		Render(); //��Ⱦ
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CD3DTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CD3DTestDlg::InitD3D()
{
	HRESULT hr=S_OK;
	//����Direct3D���󣬲���ȡ�ӿ�IDirect3D9��ָ�룬
	//���ǽ�ͨ����ָ�����Direct3D����
	m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE; //��������ģʽ��Direct3D����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//���÷���IDirect3D9::CreateDevice�����豸���󣬲���ȡ
	//�ӿ�IDirect3DDevice9��ָ�룬���ǽ�ͨ����ָ������豸����
	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, //ʹ��ȱʡ���Կ�
		D3DDEVTYPE_HAL, //ָ���豸����ΪHAL
		m_hWnd,//m_wndRender, //Direct3D���ڵľ��
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, //������㴦��
		&d3dpp, &m_pD3DDevice);

	//��Ϊʹ�ö�����ɫ��Ⱦ������Ҫ���ù��մ���
	hr=m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//�رա���ѡ�����ܣ�������Ⱦ����
	hr=m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	return hr;
}

HRESULT CD3DTestDlg::Render()
{
	HRESULT hr=S_OK;
	//��ָ����ɫ����󱸻�����
	m_pD3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0,0,100), //ָ��ʹ����ɫ
		1.0f, 0);
	//Direct3D�涨����Ⱦǰ������÷���IDirect3DDevice9::BeginScene��
	//����ʱҪ����IDirect3DDevice9::EndScene��
	m_pD3DDevice->BeginScene();
	//ʵ�ʵ���Ⱦ������ڴ˴�����Ϊ����ֻ��Ϊ����ʾ��γ�ʼ��Direct3D��
	//��������Ϊ�գ����ɵ�Direct3D���ڽ���һ����ɫ�����Ŀհ״���
	SetupMatrices();//���ñ任����
	//�����Զ����FVF
	hr=m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	//�󶨶��㻺�������豸����Դ
	hr=m_pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	//����ͼԪ�����в���1ΪͼԪ��ʽ������3Ϊ��������Ŀ
	hr=m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 3 );

	m_pD3DDevice->EndScene();
	//������ǰ/�󱸻�������ˢ�´���
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return hr;
}

void CD3DTestDlg::Cleanup()
{
	m_pVB->Release(); //�ͷŶ��㻺����
	m_pD3DDevice->Release(); //�ͷ��豸����
	m_pD3D->Release(); //�ͷ�Direct3D����
}
void CD3DTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Cleanup();
}


void CD3DTestDlg::InitGeometry()
{
	//������ʵ�����ѧģ��
	CUSTOMVERTEX vertices[] =
	{
		{ -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255,0,0) }, //��A����ɫ
		{  0.0f,  1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0) }, //��B����ɫ
		{  1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0,0,255) }  //��C����ɫ
	}; 

	//�������㻺����������ȡ�ӿ�IDirect3DVertexBuffer9��ָ��
	m_pD3DDevice->CreateVertexBuffer(
		sizeof(vertices), //�������ߴ�
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL );
	//�Ѷ����������붥�㻺����
	void* pVertices;
	m_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices, sizeof(vertices) );
	m_pVB->Unlock();
}

void CD3DTestDlg::SetupMatrices()
{
	float angle = m_nRotateY * 3.1415926f / 180; //����ת�ǻ���ɻ���
	D3DXMATRIX matWorld;

	//��������任����
	::D3DXMatrixRotationY( &matWorld, angle );
	//������任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	D3DXVECTOR3 eye( 0.0f, 0.0f,-5.0f ); //�۲��
	D3DXVECTOR3 lookat( 0.0f, 0.0f, 0.0f ); //����Ŀ���
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f ); //�Ϸ���
	D3DXMATRIX matView;
	//�����ӽǱ任����
	::D3DXMatrixLookAtLH( &matView, &eye, &lookat, &up );
	//���ӽǱ任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIXA16 matProj;
	//����͸��ͶӰ�任����
	::D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 4.0f, 100.0f );
	//��ͶӰ�任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}
int CD3DTestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_nRotateY = 0;
	SetTimer( 1, 40 ,NULL ); //��ʱ�����Ϊ40����

	return 0;
}

void CD3DTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bMoveAble)
	{
		m_nRotateY += 2; //ÿ����ת2��
		Render();
	}
	CDialog::OnTimer(nIDEvent);
}

void CD3DTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bMoveAble = !m_bMoveAble;
	CDialog::OnLButtonDown(nFlags, point);
}
