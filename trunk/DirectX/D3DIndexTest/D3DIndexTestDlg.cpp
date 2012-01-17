// D3DIndexTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "D3DIndexTest.h"
#include "D3DIndexTestDlg.h"
#include <d3d9.h>
#include <d3dx9.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD3DIndexTestDlg �Ի���


CD3DIndexTestDlg::CD3DIndexTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CD3DIndexTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nRotateY = 0;
}

void CD3DIndexTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD3DIndexTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CD3DIndexTestDlg ��Ϣ�������

BOOL CD3DIndexTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitD3D();
	InitGeometry();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

HRESULT CD3DIndexTestDlg::InitD3D()
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
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //����16 bit��Z����

	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, //ʹ��ȱʡ���Կ�
		D3DDEVTYPE_HAL, //ָ���豸����ΪHAL
		m_hWnd,//m_wndRender, //Direct3D���ڵľ��
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, //������㴦��
		&d3dpp, &m_pD3DDevice);

	//��Ϊʹ�ö�����ɫ��Ⱦ������Ҫ���ù��մ���
	//hr=m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//�򿪹��մ���
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	//����Z���棬������������
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

	//�Զ��Է���ʸ�����й�һ������
	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	//�رա���ѡ�����ܣ�������Ⱦ����
	//hr=m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	return hr;
}

struct CUSTOMVERTEX1
{
	D3DXVECTOR3 position; //��������
	D3DXVECTOR3 normal; //���㷨��
	float tu, tv;  //��������
};
#define D3DFVF_CUSTOMVERTEX1 (D3DFVF_XYZ | D3DFVF_NORMAL|D3DFVF_TEX1)
//Բ׶�����FVF��ʽ�����ꡢ���㷨��
struct CUSTOMVERTEX2
{
	D3DXVECTOR3 position; //��������
	D3DXVECTOR3 normal; //���㷨��
};
#define D3DFVF_CUSTOMVERTEX2 (D3DFVF_XYZ | D3DFVF_NORMAL)

void CD3DIndexTestDlg::InitGeometry()
{
	////����׶����ѧģ��
	//CUSTOMVERTEX vertices[] = //FVF��������
	//{{ 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0) }, //��A����ɫ
	//{ -1.0f, -1.0f, -0.577f, D3DCOLOR_XRGB(255,0,0) }, //��B����ɫ
	//{ 1.0f, -1.0f, -0.577f, D3DCOLOR_XRGB(0,255,255) }, //��C��ǳ��
	//{ 0.0f, -1.0f, 1.155f, D3DCOLOR_XRGB(255,0,255) }}; //��D���ۺ�
	//WORD indices[] = { 0, 2, 1, 0, 3, 2, 0, 1, 3, 1, 2, 3 }; //��������
	////�������㻺����������ȡ�ӿ�IDirect3DVertexBuffer9��ָ��
	//m_pD3DDevice->CreateVertexBuffer(
	//	sizeof(vertices), //�������ߴ�
	//	0, D3DFVF_CUSTOMVERTEX,
	//	D3DPOOL_DEFAULT, &m_pVB, NULL );
	////�Ѷ����������붥�㻺����
	//void* pVertices;
	//m_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	//memcpy( pVertices, vertices, sizeof(vertices) );
	//m_pVB->Unlock();
	////��������������������ȡ�ӿ�LPDIRECT3DINDEXBUFFER9��ָ��
	//m_pD3DDevice->CreateIndexBuffer(
	//	sizeof(indices), //�������ߴ�
	//	0, D3DFMT_INDEX16, //ʹ��16 bit������ֵ
	//	D3DPOOL_DEFAULT, &m_pIB, NULL );
	////������ֵ��������������
	//void *pIndices;
	//m_pIB->Lock( 0, sizeof(indices), (void**)&pIndices, 0 );
	//memcpy( pIndices, indices, sizeof(indices) );
	//m_pIB->Unlock();



	//��ͼƬ�ļ���ֱ�Ӵ����������
	::D3DXCreateTextureFromFile( m_pD3DDevice, _T("texture.jpg"), &m_pTexture );

	//����Բ׶�������ѧģ��
	CUSTOMVERTEX1 vertices1[32];
	vertices1[0].position = D3DXVECTOR3( -1.0f, 0.0f, 0.0f ); //��A������
	vertices1[0].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f ); //��A�ķ���ʸ��
	
	vertices1[0].tu = 0.0f; //��A����������
	vertices1[0].tv = 0.5f;

	for (int i = 1; i < 32; i++)
	{ //���㶥������C1��C2 ... ... C30��C1������ͷ���
		float theta = (i-1)*12*D3DX_PI/180;
		vertices1[i].position = D3DXVECTOR3( 1.0f, sin(theta), cos(theta) );
		vertices1[i].normal = D3DXVECTOR3( 0.0f, sin(theta), cos(theta) );

		//���㶥�����е���������
		float m = sqrt(5.0f);
		float beta = (0.5f - 1.0/m + (i-1.0)/15.0f/m )*D3DX_PI;
		vertices1[i].tu = 0.5*sin(beta);
		vertices1[i].tv = 0.5 - 0.5*cos(beta);
	}
	//����Բ׶����Ķ��㻺���������붥������
	m_pD3DDevice->CreateVertexBuffer(
		sizeof(vertices1), 0, D3DFVF_CUSTOMVERTEX1,
		D3DPOOL_DEFAULT, &m_pVB1, NULL );
	void* pVertices;
	m_pVB1->Lock( 0, sizeof(vertices1), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices1, sizeof(vertices1) );
	m_pVB1->Unlock();


	//����Բ׶�������ѧģ��
	CUSTOMVERTEX2 vertices2[32];
	vertices2[0].position = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ); //��B������
	vertices2[0].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ); //��B�ķ���ʸ��
	for (int i = 1; i < 32; i++)
	{ //���㶥������C1��C30��C29 ... ... C1������ͷ���
		vertices2[i].position = vertices1[32-i].position;
		vertices2[i].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	}
	//����Բ׶����Ķ��㻺���������붥������
	m_pD3DDevice->CreateVertexBuffer(
		sizeof(vertices2), 0, D3DFVF_CUSTOMVERTEX2,
		D3DPOOL_DEFAULT, &m_pVB2, NULL );
	m_pVB2->Lock( 0, sizeof(vertices2), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices2, sizeof(vertices2) );
	m_pVB2->Unlock();
}

HRESULT CD3DIndexTestDlg::Render()
{
	HRESULT hr=S_OK;
	//��ָ����ɫ����󱸻�����
	m_pD3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,100), //ָ��ʹ����ɫ
		1.0f, 0);
	//Direct3D�涨����Ⱦǰ������÷���IDirect3DDevice9::BeginScene��
	//����ʱҪ����IDirect3DDevice9::EndScene��
	m_pD3DDevice->BeginScene();
	//ʵ�ʵ���Ⱦ������ڴ˴�����Ϊ����ֻ��Ϊ����ʾ��γ�ʼ��Direct3D��
	//��������Ϊ�գ����ɵ�Direct3D���ڽ���һ����ɫ�����Ŀհ״���
	SetupMatrices();//���ñ任����

	SetLight(); //���õƹ�
	//����Բ׶�����ͼԪ
	SetMaterial1(); //ʹ�ð�ɫ�Ĳ���
	//��������볡�������в���1Ϊ����������ţ�ȡֵ��Χ0-7��
	//�ֱ�����һ���ڰ˲���������ֻ����һ���������������Ϊ0��
	m_pD3DDevice->SetTexture( 0, m_pTexture );
	//���������Ϸ�ʽΪ������ �� ���ʵ������䡱��
	//��ʵ���Բ������ã���Ϊ����Direct3Dȱʡ�Ļ�Ϸ�ʽ��
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	//�����Զ����FVF
	hr=m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX1 );
	//�󶨶��㻺�������豸����Դ
	hr=m_pD3DDevice->SetStreamSource( 0, m_pVB1, 0, sizeof(CUSTOMVERTEX1) );
	//����ͼԪ�����в���1ΪͼԪ��ʽ������3Ϊ��������Ŀ
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 30 );

	m_pD3DDevice->SetTexture( 0, NULL );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

	//����Բ׶�����ͼԪ
	SetMaterial2(); //ʹ�û�ɫ�Ĳ���
	m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX2 );
	m_pD3DDevice->SetStreamSource( 0, m_pVB2, 0, sizeof(CUSTOMVERTEX2) );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 30 );

	m_pD3DDevice->EndScene();
	//������ǰ/�󱸻�������ˢ�´���
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return hr;

}

void CD3DIndexTestDlg::SetLight()
{
	//����һ����ɫ��ƽ�й�
	D3DLIGHT9 light;
	::ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type = D3DLIGHT_DIRECTIONAL; //�ƹ�����
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Direction = D3DXVECTOR3( -1.0f, -1.0f, 0.0f );
	light.Range = 1000.0f; //�ƹ�����÷�Χ
	m_pD3DDevice->SetLight( 0, &light ); //���õƹ⣬����1Ϊ�ƹ��������
	m_pD3DDevice->LightEnable( 0, TRUE );//�򿪵ƹ⣬����1Ϊ�ƹ��������
	//���û�����
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_RGBA(32,32,32,0) );
}

void CD3DIndexTestDlg::SetMaterial1()
{
	//����һ����ɫ�Ĳ���
	D3DMATERIAL9 mtrl;
	::ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial( &mtrl ); //���ò���
}

void CD3DIndexTestDlg::SetMaterial2()
{
	//����һ����ɫ�Ĳ���
	D3DMATERIAL9 mtrl;
	::ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial( &mtrl ); //���ò���
}


void CD3DIndexTestDlg::OnPaint()
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
		Render();
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CD3DIndexTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CD3DIndexTestDlg::Cleanup()
{
//	m_pIB->Release();
//	m_pVB->Release(); //�ͷŶ��㻺����
	m_pVB1->Release();
	m_pVB2->Release();
	m_pTexture->Release(); //�ͷ��������
	m_pD3DDevice->Release(); //�ͷ��豸����
	m_pD3D->Release(); //�ͷ�Direct3D����
}


void CD3DIndexTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Cleanup();
}

void CD3DIndexTestDlg::SetupMatrices()
{
	float angle = m_nRotateY * 3.1415926f / 180; //����ת�ǻ���ɻ���

	D3DXMATRIX matWorld;
	//��������任����
	::D3DXMatrixRotationZ( &matWorld, angle + rand()/RAND_MAX);
	//������任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );

	D3DXVECTOR3 eye( 0.0f, 0.0f,-10.0f ); //�۲��
	D3DXVECTOR3 lookat( 0.0f, 0.0f, 0.0f ); //����Ŀ���
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f ); //�Ϸ���
	D3DXMATRIX matView;
	//�����ӽǱ任����
	::D3DXMatrixLookAtLH( &matView, &eye, &lookat, &up );
	//���ӽǱ任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIXA16 matProj;
	//����͸��ͶӰ�任����
	::D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	//��ͶӰ�任�������õ���Ⱦ����
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void CD3DIndexTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_nRotateY += 2; //ÿ����ת2��
	Render();
	
	CDialog::OnTimer(nIDEvent);
}

int CD3DIndexTestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer( 1, 40 ,NULL ); //��ʱ�����Ϊ40����
	return 0;
}
