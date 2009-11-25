#include "GridSpacing.h"
#include "resource.h"

// Constructor
CGridSpacing::CGridSpacing()
{
}

// Destructor
CGridSpacing::~CGridSpacing()
{
}

// Dialog Initialization
int CGridSpacing::OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam)
{
	// Get Handles to the Controls
	m_hHGrid = GetDlgItem(hDlg,IDC_HGRID);
	m_hVGrid = GetDlgItem(hDlg,IDC_VGRID);
	m_hHGridc = GetDlgItem(hDlg,IDC_HGRIDC);
	m_hVGridc = GetDlgItem(hDlg,IDC_VGRIDC);

	// Set the Horizontal Spacing
	sprintf(m_szText,"%d",m_nGridX);
	Edit_SetText(m_hHGrid,m_szText);

	// Set the Vertical Spacing
	sprintf(m_szText,"%d",m_nGridY);
	Edit_SetText(m_hVGrid,m_szText);

	// Set the Horizontal Check Box
	Button_SetCheck(m_hHGridc,m_fGridX);

	// Set the Vertical Check Box
	Button_SetCheck(m_hVGridc,m_fGridY);

	return TRUE;
}

// Dialog WM_COMMAND Handling
void CGridSpacing::OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	// Exit Status for Ok
	BOOL	fExit = TRUE;

	// Close the Dialog Box
	if (iId == IDOK)
	{
		// Get the New Values
		Edit_GetText(m_hHGrid,m_szText,10);
		m_iLength = strlen(m_szText);
		if (m_iLength > 0)
			m_nGridX = atoi(m_szText);
		else
			fExit = FALSE;

		Edit_GetText(m_hVGrid,m_szText,10);
		m_iLength = strlen(m_szText);
		if (m_iLength > 0)
			m_nGridY = atoi(m_szText);
		else
			fExit = FALSE;

		// Check the Grid Setting
		if ((m_nGridX == 0) && (m_nGridY == 0))
			fExit = FALSE;
		if ((m_nGridX > 20) || (m_nGridY > 20))
			fExit = FALSE;

		// Get the New Flags
		m_fGridX = Button_GetCheck(m_hHGridc);
		m_fGridY = Button_GetCheck(m_hVGridc);

		// End the Dialog
		if (fExit)
			EndDialog(hDlg,TRUE);
	}
	else if (iId == IDDEFAULT)
	{
		// Set the Horizontal Spacing
		sprintf(m_szText,"2");
		Edit_SetText(m_hHGrid,m_szText);

		// Set the Vertical Spacing
		sprintf(m_szText,"2");
		Edit_SetText(m_hVGrid,m_szText);

		// Set the Horizontal Check Box
		Button_SetCheck(m_hHGridc,FALSE);

		// Set the Vertical Check Box
		Button_SetCheck(m_hVGridc,FALSE);
	}
	else if (iId == IDCANCEL)
		EndDialog(hDlg,FALSE);
}
