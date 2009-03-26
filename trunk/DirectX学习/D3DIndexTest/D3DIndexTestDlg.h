// D3DIndexTestDlg.h : 头文件
//

#pragma once
#include <d3d9.h>

struct CUSTOMVERTEX
{
	float x, y, z; //顶点坐标
	DWORD color; //顶点颜色
};
//定义FVF用到的数据项：坐标 颜色
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// CD3DIndexTestDlg 对话框
class CD3DIndexTestDlg : public CDialog
{
// 构造
public:
	CD3DIndexTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_D3DINDEXTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	HRESULT InitD3D(); //该函数用于初始化Direct3D
	LPDIRECT3D9 m_pD3D; //Direct3D对象的接口指针
	LPDIRECT3DDEVICE9 m_pD3DDevice; //设备对象的接口指针
	//LPDIRECT3DINDEXBUFFER9 m_pIB; //索引缓存区的接口指针
	//LPDIRECT3DVERTEXBUFFER9 m_pVB; //顶点缓存区的的接口指针
	LPDIRECT3DVERTEXBUFFER9 m_pVB2; //顶点缓存区的的接口指针 圆锥曲面
	LPDIRECT3DVERTEXBUFFER9 m_pVB1; //顶点缓存区的的接口指针 圆锥底面
	int m_nRotateY; //实体的旋转角度（单位：度）
	LPDIRECT3DTEXTURE9 m_pTexture; //纹理对象的接口指针
	void InitGeometry();
	void Cleanup();
	HRESULT Render();
	void SetupMatrices();
	void SetLight();
	void SetMaterial1();
	void SetMaterial2();
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
