class CMyWinApp:public CWinApp
{
public:
	BOOL InitInstance();
};

class CMyFrameWnd:public CFrameWnd
{
public:
	CMyFrameWnd();
	afx_msg void OnPaint();
	afx_msg void OnAbout();

private:
	DECLARE_MESSAGE_MAP()
	static VOID CALLBACK LineDDACallback(int,int,LPARAM);
public:
	void OnOpen(void);
};