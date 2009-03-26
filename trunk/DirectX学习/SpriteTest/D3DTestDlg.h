// D3DTestDlg.h : 头文件
//

#pragma once
#include <d3d9.h>

// CD3DTestDlg 对话框
class CD3DTestDlg : public CDialog
{
// 构造
public:
	CD3DTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_D3DTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	LPDIRECT3D9 m_pD3D; //Direct3D对象的接口指针
	LPDIRECT3DDEVICE9 m_pD3DDevice; //设备对象的接口指针
	HRESULT InitD3D(); //该函数用于初始化Direct3D
	HRESULT Render();
	void Cleanup();
	LPDIRECT3DVERTEXBUFFER9 m_pVB; //顶点缓存区的的接口指针
	void InitGeometry(); //该函数用于建模
	int m_nRotateY; //实体的旋转角度（单位：度）
	void SetupMatrices(); //该函数用于设置三个变换矩阵
	BOOL m_bMoveAble;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
