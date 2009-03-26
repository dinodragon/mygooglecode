#if !defined(GRIDSPACING_H)
#define GRIDSPACING_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

// Grid Spacing Class for Message Handling
class	CGridSpacing
{
public:

	// Constructor and Destructor
	CGridSpacing();
	~CGridSpacing();

	// Member Variables
	HWND	m_hHGrid;
	HWND	m_hVGrid;
	HWND	m_hHGridc;
	HWND	m_hVGridc;
	int		m_nGridX;
	int		m_nGridY;
	BOOL	m_fGridX;
	BOOL	m_fGridY;
	char	m_szText[11];
	int		m_iLength;

	// Message Handling Function Prototypes
	BOOL	OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam);
	void	OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify);
};

#endif