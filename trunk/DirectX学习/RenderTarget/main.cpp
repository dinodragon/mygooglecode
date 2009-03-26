#include  < D3DX9.h > 
#include  < string > 
typedef std:: string  String;
#define  SAFE_RELEASE(o) {if(o){o->Release();o = 0;}} 


LPDIRECT3D9 g_pD3D  =   0 ;                 //  D3D Driver 
LPDIRECT3DDEVICE9 g_pd3dDevice  =   0 ;     //  D3D 设备 
D3DCAPS9 g_Caps  =    {(D3DDEVTYPE) 0 } ;     //  D3D 的帽子 
LPD3DXMESH g_pMeshTeapot  =   0 ;     //  茶壶顶点缓冲区 
LPDIRECT3DVERTEXBUFFER9 g_pVB  =   0 ;     //  顶点缓冲区 
LPDIRECT3DINDEXBUFFER9 g_pIB  =   0 ;     //  索引缓冲区 
LPDIRECT3DTEXTURE9 g_pTexture  =   0 ;     //  贴图 
LPDIRECT3DTEXTURE9 g_pRenderTexture  =   0 ;     //  渲染到贴图 
LPDIRECT3DSURFACE9 g_pRenderSurface  =   0 ;     //  渲染到贴图的表面
//  顶点定义 
#define  D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1) 
struct  CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	float  u , v;
} ;

//  错误记录 
void  D3DErr(String strMsg)
{
	MessageBox( 0  , strMsg.c_str() ,  " 错误 "  , MB_OK);
} 

//  初始化顶点缓冲区 
HRESULT InitVB()
{
	//  创建茶壶 
	if (FAILED(D3DXCreateTeapot(g_pd3dDevice ,  & g_pMeshTeapot ,  0 )))
		return  E_FAIL;
	//  创建顶点缓冲区 
	if (FAILED(g_pd3dDevice -> CreateVertexBuffer( 4   *   sizeof (CUSTOMVERTEX) ,  0  , D3DFVF_CUSTOMVERTEX , D3DPOOL_DEFAULT ,  & g_pVB ,  0 )))
		return  E_FAIL;

	CUSTOMVERTEX  * pVertecies;
	//  锁定缓冲区 
	if (SUCCEEDED(g_pVB -> Lock( 0  ,  0  , ( void ** ) & pVertecies ,  0 )))
	{
		pVertecies[ 0 ].position  =  D3DXVECTOR3( - 1  ,  1  ,  0 );
		pVertecies[ 1 ].position  =  D3DXVECTOR3( - 1  ,  - 1  ,  0 );
		pVertecies[ 2 ].position  =  D3DXVECTOR3( 1  ,  1  ,  0 );
		pVertecies[ 3 ].position  =  D3DXVECTOR3( 1  ,  - 1  ,  0 );

		pVertecies[ 0 ].u  =   0 ;
		pVertecies[ 0 ].v  =   0 ;

		pVertecies[ 1 ].u  =   0 ;
		pVertecies[ 1 ].v  =   1 ;

		pVertecies[ 2 ].u  =   1 ;
		pVertecies[ 2 ].v  =   0 ;

		pVertecies[ 3 ].u  =   1 ;
		pVertecies[ 3 ].v  =   1 ;

		pVertecies[ 0 ].color  =   0xFFFFFFFF ;
		pVertecies[ 1 ].color  =   0xFFFFFFFF ;
		pVertecies[ 2 ].color  =   0xFFFFFFFF ;
		pVertecies[ 3 ].color  =   0xFFFFFFFF ;
		g_pVB -> Unlock();
	} 
	else 
	{
		return  E_FAIL;
	} 

	//  载入纹理 
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice ,  "BRICE.JPG"  ,  & g_pTexture)))
	{
		D3DErr( " 无法载入纹理Brice.jpg " );
		return  E_FAIL;
	} 

	//  创建渲染到贴图的表面 
	if (FAILED(g_pd3dDevice -> CreateTexture( 512  ,  512  ,  1  , D3DUSAGE_RENDERTARGET , D3DFMT_A8R8G8B8 , D3DPOOL_DEFAULT ,  & g_pRenderTexture ,  0 )))
	{
		D3DErr( " 无法创建渲染贴图 " );
		return  E_FAIL;
	} 
	//  获取贴图的渲染表面 
	if (FAILED(g_pRenderTexture -> GetSurfaceLevel( 0  ,  & g_pRenderSurface)))
	{
		return  E_FAIL;
	} 
	return  S_OK;
} 

//  初始化模型 
HRESULT InitGeometry()
{
	//  创建顶点缓冲区 
	if (FAILED(InitVB()))
		return  E_FAIL;
	return  S_OK;
} 

//  设置矩阵变换 
void  SetTransform()
{

	//  世界变换 
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( & matWorld);
	//  设置世界矩阵 
	g_pd3dDevice -> SetTransform(D3DTS_WORLD ,  & matWorld);
	//  Set up our view matrix. A view matrix can be defined given an eye point,
	//  a point to lookat, and a direction for which way is up. Here, we set the
	//  eye five units back along the z-axis and up three units, look at the
	//  origin, and define "up" to be in the y-direction.
	//  视口变换 
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( & matView ,  & D3DXVECTOR3( 0  ,  0  ,  - 5 )
		,  & D3DXVECTOR3( 0  ,  0  ,  0 ) 
		,  & D3DXVECTOR3( 0  ,  1  ,  0 ));
	g_pd3dDevice -> SetTransform(D3DTS_VIEW ,  & matView);
	//  For the projection matrix, we set up a perspective transform (which
	//  transforms geometry from 3D view space to 2D viewport space, with
	//  a perspective divide making objects smaller in the distance). To build
	//  a perpsective transform, we need the field of view (1/4 pi is common),
	//  the aspect ratio, and the near and far clipping planes (which define at
	//  what distances geometry should be no longer be rendered). 
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(  & matProj, D3DX_PI / 4 ,  800.0f   /   600.0f ,  1.0f ,  100.0f  );
	g_pd3dDevice -> SetTransform( D3DTS_PROJECTION,  & matProj );


} 

//  渲染场景 
void  Render()
{
	if (g_pd3dDevice)
	{
		LPDIRECT3DSURFACE9 pRenderTarget;
		//  保存渲染表面 
	//	g_pd3dDevice -> GetRenderTarget( 0  ,  & pRenderTarget);
		//  设置我们的贴图表面 
		//g_pd3dDevice -> SetRenderTarget( 0  , g_pRenderSurface);
		//  清空场景，渲染到贴图的背景是蓝色的 
		g_pd3dDevice -> Clear( 0  ,  0  , D3DCLEAR_TARGET  |  D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 0  ,  0  ,  0xFF ) ,  1  ,  0 );
		//  开始渲染到贴图 
		if (SUCCEEDED(g_pd3dDevice -> BeginScene()))
		{
			//  设置通常的矩阵 
			SetTransform();
			D3DXMATRIX matWorld;
			//  旋转茶壶 
			D3DXMatrixRotationAxis( & matWorld ,  & D3DXVECTOR3( 1  ,  0  , 1 ) , D3DX_PI  *   2.0f   *  (GetTickCount()  %   5000 )  /   5000.0f );
			g_pd3dDevice -> SetTransform(D3DTS_WORLD ,  & matWorld);

			//  设置渲染到表面的投影矩阵（这里可有可无，因为我们的窗口创建是512×512的） 
			D3DXMATRIXA16 matProj;
			D3DXMatrixPerspectiveFovLH(  & matProj, D3DX_PI / 4 ,  1.0f ,  1.0f ,  100.0f  );
			g_pd3dDevice -> SetTransform( D3DTS_PROJECTION,  & matProj );

			//  设置贴图 
			g_pd3dDevice -> SetTexture( 0  , g_pTexture);
			g_pd3dDevice -> SetSamplerState( 0  , D3DSAMP_ADDRESSU , D3DTADDRESS_MIRROR);
			g_pd3dDevice -> SetSamplerState( 0  , D3DSAMP_ADDRESSV , D3DTADDRESS_MIRROR);
			//  自动生成纹理坐标 
			g_pd3dDevice -> SetTextureStageState( 0 , D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			g_pd3dDevice -> SetTextureStageState( 0 , D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_SPHEREMAP);
			g_pd3dDevice -> SetRenderState(D3DRS_LIGHTING , FALSE);
			//  渲染茶壶 
			g_pMeshTeapot -> DrawSubset( 0 );
			g_pd3dDevice -> EndScene();
		} 


		//  恢复渲染表面为显示器 
	//	g_pd3dDevice -> SetRenderTarget( 0  , pRenderTarget);

		//  清空场景，真实场景是红色背景的 
		g_pd3dDevice -> Clear( 0  ,  0  , D3DCLEAR_TARGET  |  D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 0xFF  ,  0xFF  ,  0 ) ,  1  ,  0 );
		//  开始渲染真实场景 
		if (SUCCEEDED(g_pd3dDevice -> BeginScene()))
		{
			SetTransform();
			D3DXMATRIX matWorld;
			//  旋转表面 
			D3DXMatrixRotationAxis( & matWorld ,  & D3DXVECTOR3( 1  ,  1  , 0 ) , sinf(D3DX_PI  *   2.0f   *  (GetTickCount()  %   5000 )  /   5000.0f ));
			//  设置世界矩阵 
			g_pd3dDevice -> SetTransform(D3DTS_WORLD ,  & matWorld);
			//  设置已经渲染到表面的贴图 
			g_pd3dDevice -> SetTexture( 0  , g_pRenderTexture);
			g_pd3dDevice -> SetTextureStageState( 0 , D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
			g_pd3dDevice -> SetTextureStageState( 0 , D3DTSS_TEXCOORDINDEX,  0 );

			g_pd3dDevice -> SetSamplerState( 0  , D3DSAMP_ADDRESSU , D3DTADDRESS_MIRROR);
			g_pd3dDevice -> SetSamplerState( 0  , D3DSAMP_ADDRESSV , D3DTADDRESS_MIRROR);
			g_pd3dDevice -> SetRenderState(D3DRS_LIGHTING , FALSE);
			// g_pd3dDevice->SetRenderState(D3DRS_FILLMODE , D3DFILL_WIREFRAME); 
			g_pd3dDevice -> SetStreamSource( 0  , g_pVB ,  0  ,  sizeof (CUSTOMVERTEX));
			g_pd3dDevice -> SetFVF(D3DFVF_CUSTOMVERTEX);
			g_pd3dDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP ,  0  ,  2 );
			g_pd3dDevice -> EndScene();
		} 
		//  显示 
		g_pd3dDevice -> Present( 0  ,  0  ,  0  ,  0 );
	} 
} 

//  初始化 D3D 设备 
HRESULT InitD3D(HWND hWnd)
{
	//  创建 D3D Driver 
	if (NULL  ==  (g_pD3D  =  Direct3DCreate9(D3D_SDK_VERSION)))
	{
		D3DErr( " 无法创建Direct3D9设备 " );
		return  E_FAIL;
	} 
	//  获取当前显示模式 
	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT ,  & d3ddm)))
	{
		D3DErr( " 无法获取D3D显示器模式 " );
		return  E_FAIL;
	} 

	RECT rect;
	::GetClientRect(hWnd ,  & rect);

	//  填充参数 
	D3DPRESENT_PARAMETERS d3dpp;
	memset( & d3dpp ,  0  ,  sizeof (d3dpp));
	d3dpp.BackBufferFormat  =  d3ddm.Format;
	d3dpp.BackBufferWidth  =  rect.right;
	d3dpp.BackBufferHeight  =  rect.bottom;
	d3dpp.SwapEffect  =  D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed  =   true ;
	d3dpp.AutoDepthStencilFormat  =  D3DFMT_D16;
	d3dpp.EnableAutoDepthStencil  =  TRUE;

	//  获取帽子 
	if (FAILED(g_pD3D -> GetDeviceCaps(D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL ,  & g_Caps)))
	{
		D3DErr( " 获取D3D 帽子时发生错误 " );
		return  E_FAIL;
	} 

	//  创建D3D设备 
	if (FAILED(g_pD3D -> CreateDevice(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, hWnd
		//  检查是否支持硬件顶点处理 
		, g_Caps.DevCaps  &  D3DDEVCAPS_HWTRANSFORMANDLIGHT  ?  D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING
		,  & d3dpp
		,  & g_pd3dDevice
		)
		))
	{
		D3DErr( " 创建D3D设备时发生错误 " );
		return  E_FAIL;
	} 
	g_pd3dDevice -> SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice -> SetRenderState( D3DRS_ZENABLE, TRUE );

	if (FAILED(InitGeometry()))
		return  E_FAIL;
	return  S_OK;
} 

//  清空所有占用的资源 
void  CleanUp()
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pIB);
	SAFE_RELEASE(g_pVB);
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
} 


//  消息处理 
LRESULT WINAPI MsgProc(HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam)
{
	switch (message)
	{
	case  WM_DESTROY:
		CleanUp();
		PostQuitMessage( 0 );
		break ;
	} 
	return  ::DefWindowProc(hWnd, message , wParam , lParam);
} 

//  Windows 入口 
int  WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN  int  nShowCmd )
{
	WNDCLASS wndClass;
	memset( & wndClass ,  0  ,  sizeof (wndClass));
	wndClass.hInstance  =  hInstance;
	wndClass.lpszClassName  =   " 渲染到纹理 " ;
	wndClass.lpfnWndProc  =  MsgProc;
	RegisterClass( & wndClass);

	//  创建窗口 
	HWND hWnd  =  CreateWindow( " 渲染到纹理 "  ,  " 渲染到纹理！ "  
		,  0  ,  0  ,  0  ,  640  , 480  , GetDesktopWindow()
		,  0  , wndClass.hInstance ,  0 );
	//  显示窗口 
	ShowWindow(hWnd , SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//  初始化 D3D 设备 
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		//  消息处理循环 
		MSG msg;
		memset( & msg ,  0  ,  sizeof (msg));
		while (msg.message  !=  WM_QUIT)
		{
			if (PeekMessage( & msg ,  0  ,  0  ,  0  , PM_REMOVE))
			{
				TranslateMessage( & msg);
				DispatchMessage( & msg);
			} 
			else 
			{
				Render();
			} 
		} 
	} 
	//  清空场景 
	CleanUp();

	UnregisterClass( " 渲染到纹理 "  , wndClass.hInstance);

	return   0 ;
} 