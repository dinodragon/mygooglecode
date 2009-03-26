// D3DTestDlg.cpp : 实现文件
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
	float x, y, z; //顶点坐标
	DWORD color; //顶点颜色
};
//定义FVF用到的数据项：坐标 颜色
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// CD3DTestDlg 对话框

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


// CD3DTestDlg 消息处理程序

BOOL CD3DTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	InitD3D(); //D3D初始化
	InitGeometry(); //进行建模

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CD3DTestDlg::OnPaint()
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
		Render(); //渲染
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CD3DTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CD3DTestDlg::InitD3D()
{
	HRESULT hr=S_OK;
	//创建Direct3D对象，并获取接口IDirect3D9的指针，
	//我们将通过该指针操作Direct3D对象。
	m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE; //创建窗口模式的Direct3D程序
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//调用方法IDirect3D9::CreateDevice创建设备对象，并获取
	//接口IDirect3DDevice9的指针，我们将通过该指针操作设备对象
	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, //使用缺省的显卡
		D3DDEVTYPE_HAL, //指定设备类型为HAL
		m_hWnd,//m_wndRender, //Direct3D窗口的句柄
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, //软件顶点处理
		&d3dpp, &m_pD3DDevice);

	//因为使用顶点颜色渲染，所以要禁用光照处理
	hr=m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//关闭“挑选”功能，允许渲染背面
	hr=m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	return hr;
}

HRESULT CD3DTestDlg::Render()
{
	HRESULT hr=S_OK;
	//用指定颜色清除后备缓存区
	m_pD3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0,0,100), //指定使用蓝色
		1.0f, 0);
	//Direct3D规定在渲染前必须调用方法IDirect3DDevice9::BeginScene，
	//结束时要调用IDirect3DDevice9::EndScene。
	m_pD3DDevice->BeginScene();
	//实际的渲染代码放在此处。因为本节只是为了演示如何初始化Direct3D，
	//所以这里为空，生成的Direct3D窗口将是一个蓝色背景的空白窗口
	SetupMatrices();//设置变换矩阵
	//设置自定义的FVF
	hr=m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	//绑定顶点缓存区至设备数据源
	hr=m_pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	//绘制图元，其中参数1为图元格式，参数3为三角形数目
	hr=m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 3 );

	m_pD3DDevice->EndScene();
	//交换当前/后备缓存区，刷新窗口
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return hr;
}

void CD3DTestDlg::Cleanup()
{
	m_pVB->Release(); //释放顶点缓存区
	m_pD3DDevice->Release(); //释放设备对象
	m_pD3D->Release(); //释放Direct3D对象
}
void CD3DTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Cleanup();
}


void CD3DTestDlg::InitGeometry()
{
	//三角形实体的数学模型
	CUSTOMVERTEX vertices[] =
	{
		{ -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255,0,0) }, //点A，红色
		{  0.0f,  1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0) }, //点B，绿色
		{  1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0,0,255) }  //点C，蓝色
	}; 

	//创建顶点缓存区，并获取接口IDirect3DVertexBuffer9的指针
	m_pD3DDevice->CreateVertexBuffer(
		sizeof(vertices), //缓存区尺寸
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL );
	//把顶点数据填入顶点缓存区
	void* pVertices;
	m_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices, sizeof(vertices) );
	m_pVB->Unlock();
}

void CD3DTestDlg::SetupMatrices()
{
	float angle = m_nRotateY * 3.1415926f / 180; //把旋转角换算成弧度
	D3DXMATRIX matWorld;

	//计算世界变换矩阵
	::D3DXMatrixRotationY( &matWorld, angle );
	//把世界变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	D3DXVECTOR3 eye( 0.0f, 0.0f,-5.0f ); //观察点
	D3DXVECTOR3 lookat( 0.0f, 0.0f, 0.0f ); //视线目标点
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f ); //上方向
	D3DXMATRIX matView;
	//计算视角变换矩阵
	::D3DXMatrixLookAtLH( &matView, &eye, &lookat, &up );
	//把视角变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIXA16 matProj;
	//计算透视投影变换矩阵
	::D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 4.0f, 100.0f );
	//把投影变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}
int CD3DTestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_nRotateY = 0;
	SetTimer( 1, 40 ,NULL ); //定时间隔设为40毫秒

	return 0;
}

void CD3DTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMoveAble)
	{
		m_nRotateY += 2; //每次旋转2度
		Render();
	}
	CDialog::OnTimer(nIDEvent);
}

void CD3DTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bMoveAble = !m_bMoveAble;
	CDialog::OnLButtonDown(nFlags, point);
}
