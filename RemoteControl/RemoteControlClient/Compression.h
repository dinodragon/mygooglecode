#if !defined(COMPRESSION_H)
#define COMPRESSION_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>


// Compression Level Class for Message Handling
class	CCompression
{
public:

	// Constructor and Destructor
	CCompression();
	~CCompression();

	// Message Handling Function Prototypes
	BOOL	OnInitDialog(HWND hDlg,HWND hwndFocus, LPARAM lParam);
	void	OnCommand(HWND hDlg,int iId,HWND hWndCtl,UINT iCodeNotify);

	// Variables
	int		m_iCompressionLevel;
};

#endif