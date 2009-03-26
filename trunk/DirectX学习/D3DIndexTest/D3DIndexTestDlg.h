// D3DIndexTestDlg.h : ͷ�ļ�
//

#pragma once
#include <d3d9.h>

struct CUSTOMVERTEX
{
	float x, y, z; //��������
	DWORD color; //������ɫ
};
//����FVF�õ������������ ��ɫ
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// CD3DIndexTestDlg �Ի���
class CD3DIndexTestDlg : public CDialog
{
// ����
public:
	CD3DIndexTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_D3DINDEXTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	HRESULT InitD3D(); //�ú������ڳ�ʼ��Direct3D
	LPDIRECT3D9 m_pD3D; //Direct3D����Ľӿ�ָ��
	LPDIRECT3DDEVICE9 m_pD3DDevice; //�豸����Ľӿ�ָ��
	//LPDIRECT3DINDEXBUFFER9 m_pIB; //�����������Ľӿ�ָ��
	//LPDIRECT3DVERTEXBUFFER9 m_pVB; //���㻺�����ĵĽӿ�ָ��
	LPDIRECT3DVERTEXBUFFER9 m_pVB2; //���㻺�����ĵĽӿ�ָ�� Բ׶����
	LPDIRECT3DVERTEXBUFFER9 m_pVB1; //���㻺�����ĵĽӿ�ָ�� Բ׶����
	int m_nRotateY; //ʵ�����ת�Ƕȣ���λ���ȣ�
	LPDIRECT3DTEXTURE9 m_pTexture; //�������Ľӿ�ָ��
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
