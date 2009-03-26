// D3DIndexTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "D3DIndexTest.h"
#include "D3DIndexTestDlg.h"
#include <d3d9.h>
#include <d3dx9.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD3DIndexTestDlg 对话框


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


// CD3DIndexTestDlg 消息处理程序

BOOL CD3DIndexTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitD3D();
	InitGeometry();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

HRESULT CD3DIndexTestDlg::InitD3D()
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
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //生成16 bit的Z缓存

	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, //使用缺省的显卡
		D3DDEVTYPE_HAL, //指定设备类型为HAL
		m_hWnd,//m_wndRender, //Direct3D窗口的句柄
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, //软件顶点处理
		&d3dpp, &m_pD3DDevice);

	//因为使用顶点颜色渲染，所以要禁用光照处理
	//hr=m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//打开光照处理
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	//启用Z缓存，允许消隐处理
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

	//自动对法线矢量进行归一化处理
	m_pD3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	//关闭“挑选”功能，允许渲染背面
	//hr=m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	return hr;
}

struct CUSTOMVERTEX1
{
	D3DXVECTOR3 position; //顶点坐标
	D3DXVECTOR3 normal; //顶点法线
	float tu, tv;  //纹理坐标
};
#define D3DFVF_CUSTOMVERTEX1 (D3DFVF_XYZ | D3DFVF_NORMAL|D3DFVF_TEX1)
//圆锥底面的FVF格式：坐标、顶点法线
struct CUSTOMVERTEX2
{
	D3DXVECTOR3 position; //顶点坐标
	D3DXVECTOR3 normal; //顶点法线
};
#define D3DFVF_CUSTOMVERTEX2 (D3DFVF_XYZ | D3DFVF_NORMAL)

void CD3DIndexTestDlg::InitGeometry()
{
	////三棱锥的数学模型
	//CUSTOMVERTEX vertices[] = //FVF顶点数据
	//{{ 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0) }, //点A，绿色
	//{ -1.0f, -1.0f, -0.577f, D3DCOLOR_XRGB(255,0,0) }, //点B，红色
	//{ 1.0f, -1.0f, -0.577f, D3DCOLOR_XRGB(0,255,255) }, //点C，浅蓝
	//{ 0.0f, -1.0f, 1.155f, D3DCOLOR_XRGB(255,0,255) }}; //点D，粉红
	//WORD indices[] = { 0, 2, 1, 0, 3, 2, 0, 1, 3, 1, 2, 3 }; //索引序列
	////创建顶点缓存区，并获取接口IDirect3DVertexBuffer9的指针
	//m_pD3DDevice->CreateVertexBuffer(
	//	sizeof(vertices), //缓存区尺寸
	//	0, D3DFVF_CUSTOMVERTEX,
	//	D3DPOOL_DEFAULT, &m_pVB, NULL );
	////把顶点数据填入顶点缓存区
	//void* pVertices;
	//m_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	//memcpy( pVertices, vertices, sizeof(vertices) );
	//m_pVB->Unlock();
	////创建索引缓存区，并获取接口LPDIRECT3DINDEXBUFFER9的指针
	//m_pD3DDevice->CreateIndexBuffer(
	//	sizeof(indices), //缓存区尺寸
	//	0, D3DFMT_INDEX16, //使用16 bit的索引值
	//	D3DPOOL_DEFAULT, &m_pIB, NULL );
	////把索引值填入索引缓存区
	//void *pIndices;
	//m_pIB->Lock( 0, sizeof(indices), (void**)&pIndices, 0 );
	//memcpy( pIndices, indices, sizeof(indices) );
	//m_pIB->Unlock();



	//从图片文件中直接创建纹理对象
	::D3DXCreateTextureFromFile( m_pD3DDevice, _T("texture.jpg"), &m_pTexture );

	//建立圆锥曲面的数学模型
	CUSTOMVERTEX1 vertices1[32];
	vertices1[0].position = D3DXVECTOR3( -1.0f, 0.0f, 0.0f ); //点A的坐标
	vertices1[0].normal = D3DXVECTOR3( -1.0f, 0.0f, 0.0f ); //点A的法线矢量
	
	vertices1[0].tu = 0.0f; //点A的纹理坐标
	vertices1[0].tv = 0.5f;

	for (int i = 1; i < 32; i++)
	{ //计算顶点序列C1、C2 ... ... C30、C1的坐标和法线
		float theta = (i-1)*12*D3DX_PI/180;
		vertices1[i].position = D3DXVECTOR3( 1.0f, sin(theta), cos(theta) );
		vertices1[i].normal = D3DXVECTOR3( 0.0f, sin(theta), cos(theta) );

		//计算顶点序列的纹理坐标
		float m = sqrt(5.0f);
		float beta = (0.5f - 1.0/m + (i-1.0)/15.0f/m )*D3DX_PI;
		vertices1[i].tu = 0.5*sin(beta);
		vertices1[i].tv = 0.5 - 0.5*cos(beta);
	}
	//创建圆锥曲面的顶点缓存区，填入顶点数据
	m_pD3DDevice->CreateVertexBuffer(
		sizeof(vertices1), 0, D3DFVF_CUSTOMVERTEX1,
		D3DPOOL_DEFAULT, &m_pVB1, NULL );
	void* pVertices;
	m_pVB1->Lock( 0, sizeof(vertices1), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices1, sizeof(vertices1) );
	m_pVB1->Unlock();


	//建立圆锥底面的数学模型
	CUSTOMVERTEX2 vertices2[32];
	vertices2[0].position = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ); //点B的坐标
	vertices2[0].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ); //点B的法线矢量
	for (int i = 1; i < 32; i++)
	{ //计算顶点序列C1、C30、C29 ... ... C1的坐标和法线
		vertices2[i].position = vertices1[32-i].position;
		vertices2[i].normal = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	}
	//创建圆锥底面的顶点缓存区，填入顶点数据
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
	//用指定颜色清除后备缓存区
	m_pD3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,100), //指定使用蓝色
		1.0f, 0);
	//Direct3D规定在渲染前必须调用方法IDirect3DDevice9::BeginScene，
	//结束时要调用IDirect3DDevice9::EndScene。
	m_pD3DDevice->BeginScene();
	//实际的渲染代码放在此处。因为本节只是为了演示如何初始化Direct3D，
	//所以这里为空，生成的Direct3D窗口将是一个蓝色背景的空白窗口
	SetupMatrices();//设置变换矩阵

	SetLight(); //设置灯光
	//绘制圆锥曲面的图元
	SetMaterial1(); //使用白色的材质
	//把纹理加入场景，其中参数1为纹理的索引号，取值范围0-7，
	//分别代表第一至第八层纹理。这里只用了一层纹理，因此索引号为0。
	m_pD3DDevice->SetTexture( 0, m_pTexture );
	//设置纹理混合方式为“纹理 × 材质的漫反射”。
	//其实可以不用设置，因为这是Direct3D缺省的混合方式。
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	//设置自定义的FVF
	hr=m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX1 );
	//绑定顶点缓存区至设备数据源
	hr=m_pD3DDevice->SetStreamSource( 0, m_pVB1, 0, sizeof(CUSTOMVERTEX1) );
	//绘制图元，其中参数1为图元格式，参数3为三角形数目
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 30 );

	m_pD3DDevice->SetTexture( 0, NULL );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

	//绘制圆锥底面的图元
	SetMaterial2(); //使用黄色的材质
	m_pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX2 );
	m_pD3DDevice->SetStreamSource( 0, m_pVB2, 0, sizeof(CUSTOMVERTEX2) );
	m_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 30 );

	m_pD3DDevice->EndScene();
	//交换当前/后备缓存区，刷新窗口
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return hr;

}

void CD3DIndexTestDlg::SetLight()
{
	//创建一个白色的平行光
	D3DLIGHT9 light;
	::ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type = D3DLIGHT_DIRECTIONAL; //灯光类型
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Direction = D3DXVECTOR3( -1.0f, -1.0f, 0.0f );
	light.Range = 1000.0f; //灯光的作用范围
	m_pD3DDevice->SetLight( 0, &light ); //设置灯光，参数1为灯光的索引号
	m_pD3DDevice->LightEnable( 0, TRUE );//打开灯光，参数1为灯光的索引号
	//设置环境光
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_RGBA(32,32,32,0) );
}

void CD3DIndexTestDlg::SetMaterial1()
{
	//创建一个白色的材质
	D3DMATERIAL9 mtrl;
	::ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial( &mtrl ); //设置材质
}

void CD3DIndexTestDlg::SetMaterial2()
{
	//创建一个黄色的材质
	D3DMATERIAL9 mtrl;
	::ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial( &mtrl ); //设置材质
}


void CD3DIndexTestDlg::OnPaint()
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
		Render();
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CD3DIndexTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CD3DIndexTestDlg::Cleanup()
{
//	m_pIB->Release();
//	m_pVB->Release(); //释放顶点缓存区
	m_pVB1->Release();
	m_pVB2->Release();
	m_pTexture->Release(); //释放纹理对象
	m_pD3DDevice->Release(); //释放设备对象
	m_pD3D->Release(); //释放Direct3D对象
}


void CD3DIndexTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Cleanup();
}

void CD3DIndexTestDlg::SetupMatrices()
{
	float angle = m_nRotateY * 3.1415926f / 180; //把旋转角换算成弧度

	D3DXMATRIX matWorld;
	//计算世界变换矩阵
	::D3DXMatrixRotationZ( &matWorld, angle + rand()/RAND_MAX);
	//把世界变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );

	D3DXVECTOR3 eye( 0.0f, 0.0f,-10.0f ); //观察点
	D3DXVECTOR3 lookat( 0.0f, 0.0f, 0.0f ); //视线目标点
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f ); //上方向
	D3DXMATRIX matView;
	//计算视角变换矩阵
	::D3DXMatrixLookAtLH( &matView, &eye, &lookat, &up );
	//把视角变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIXA16 matProj;
	//计算透视投影变换矩阵
	::D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	//把投影变换矩阵设置到渲染环境
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void CD3DIndexTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_nRotateY += 2; //每次旋转2度
	Render();
	
	CDialog::OnTimer(nIDEvent);
}

int CD3DIndexTestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer( 1, 40 ,NULL ); //定时间隔设为40毫秒
	return 0;
}
