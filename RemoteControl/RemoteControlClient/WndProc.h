// CallBack Function Prototype and Window Initialization Prototypes
HWND				WinInit(HINSTANCE hInst,int iShow);
LRESULT	CALLBACK	WndProc (HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam);

// CallBack Function Prototype for ServerIP Dialog
LRESULT	CALLBACK	ServerIPDlgProc(HWND hDlg,UINT iMsg,WPARAM wParam,LPARAM lParam);

// CallBack Function Prototype for Compression Dialog
LRESULT CALLBACK	CompressionDlgProc(HWND hDlg,UINT iMsg,WPARAM wParam,LPARAM lParam);

// CallBack Function Prototype for Grid Spacing Dialog
LRESULT CALLBACK	GridSpacingDlgProc(HWND hDlg,UINT iMsg,WPARAM wParam,LPARAM lParam);

// CallBack Function Prototype for Color Mode Dialog
LRESULT CALLBACK	ColorModeDlgProc(HWND hDlg,UINT iMsg,WPARAM wParam,LPARAM lParam);
