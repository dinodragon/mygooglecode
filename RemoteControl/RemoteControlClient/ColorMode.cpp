#include "ColorMode.h"
#include "resource.h"

// Constructor
CColorMode::CColorMode()
{
}

// Destructor
CColorMode::~CColorMode()
{
}

// Dialog Initialization
int CColorMode::OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam)
{
	// Set the Color Mode Radio Button
	if (m_bmBitsPixel == 4)
		Button_SetCheck(GetDlgItem(hDlg,IDC_RADIO0),TRUE);
	else
		Button_SetCheck(GetDlgItem(hDlg,IDC_RADIO1),TRUE);

	return TRUE;
}

// Dialog WM_COMMAND Handling
void CColorMode::OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDOK)
	{
		// Set the New Color Mode
		if (Button_GetState(GetDlgItem(hDlg,IDC_RADIO0)))
			m_bmBitsPixel = 4;
		else if (Button_GetState(GetDlgItem(hDlg,IDC_RADIO1)))
			m_bmBitsPixel = 8;

		// End the Dialog
		EndDialog(hDlg,TRUE);
	}
	else if (iId == IDCANCEL)
		EndDialog(hDlg,FALSE);
}
