#if !defined(SERVERIP_H)
#define SERVERIP_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

// ServerIP Class For Message Handling
class	CServerIP
{
public:

	// Constructor and Destructor
	CServerIP();
	~CServerIP();

	// Message Handling Function Prototypes
	BOOL	OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam);
	void	OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify);

	// Variables
	char	szIP[255];
};

#endif