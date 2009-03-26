// D3DTestDlg.h : ͷ�ļ�
//

#pragma once
#include <d3d9.h>

// CD3DTestDlg �Ի���
class CD3DTestDlg : public CDialog
{
// ����
public:
	CD3DTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_D3DTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	LPDIRECT3D9 m_pD3D; //Direct3D����Ľӿ�ָ��
	LPDIRECT3DDEVICE9 m_pD3DDevice; //�豸����Ľӿ�ָ��
	HRESULT InitD3D(); //�ú������ڳ�ʼ��Direct3D
	HRESULT Render();
	void Cleanup();
	LPDIRECT3DVERTEXBUFFER9 m_pVB; //���㻺�����ĵĽӿ�ָ��
	void InitGeometry(); //�ú������ڽ�ģ
	int m_nRotateY; //ʵ�����ת�Ƕȣ���λ���ȣ�
	void SetupMatrices(); //�ú����������������任����
	BOOL m_bMoveAble;

	// ���ɵ���Ϣӳ�亯��
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
