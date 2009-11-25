#include "ServerIP.h"
#include "resource.h"

// Handle to the Server IP edit Box
HWND	hServerIP;

// Constructor
CServerIP::CServerIP()
{
}

// Destructor
CServerIP::~CServerIP()
{
}

// Dialog Initialization
int CServerIP::OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam)
{
	// Get the Handle to the Server IP Edit Box
	hServerIP = GetDlgItem(hDlg,IDC_SERVERIP);

	// Set the Initial IP Address
	SetWindowText(hServerIP,szIP);

	return TRUE;
}

// Dialog WM_COMMAND Handling
void CServerIP::OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDOK)
	{
		// Get the IP Address from the Dialog Box
		GetWindowText(hServerIP,szIP,sizeof(szIP));

		// End the Dialog
		EndDialog(hDlg,TRUE);
	}
	else if (iId == IDCANCEL)
		EndDialog(hDlg,FALSE);
}
