#if !defined(COLORMODE_H)
#define COLORMODE_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>


// Compression Level Class for Message Handling
class	CColorMode
{
public:

	// Constructor and Destructor
	CColorMode();
	~CColorMode();

	// Message Handling Function Prototypes
	BOOL	OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam);
	void	OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify);

	// Variables
	int		m_bmBitsPixel;
};

#endif