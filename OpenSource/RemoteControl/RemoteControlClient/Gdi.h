#if !defined(GDI_H)
#define GDI_H

#include <windows.h>

// The GDI Data Structure
struct GdiDS
{
	// Pointer to the Global Region DIB
	char	*pDIBitmap;

	// Pointer to the Received DIB Data
	char	*pDIB;
	char	*pStartDIB;

	// Grid Coordinates
	int		iGridX;
	int		iGridY;

	// DIB Rectangular Region
	int		iWidth1;
	int		iWidth2;
	int		iHeight1;
	int		iHeight2;

	// DIB Info Header
	LPBITMAPINFOHEADER	lpBitmapIH;

	// DIB Flags
	BOOL	fDIBitmap;
};

// The Gdi Linked List
struct GdiList
{
	struct	GdiDS	Gdi;
	struct	GdiList	*pNext;
};

// Function Prototypes
struct	GdiList	*Add_Gdi(struct GdiList *pNode,struct GdiDS Gdi);
void			Clear_Gdi(struct GdiList *pStart);

#endif // #define GDI_H