#if !defined(GDI_H)
#define GDI_H

#include <windows.h>

// The GDI Data Structure
struct GdiDS
{
	// Grid Coordinates
	int		iGridX;
	int		iGridY;

	// Rectangular Area of the Grid
	int		iWidth1;
	int		iWidth2;
	int		iHeight1;
	int		iHeight2;

	// Number of Colors in DIB Color Table
	int		nColors;

	// Number of Bytes in the DIB Information Header
	DWORD	dwBitMapHeader;

	// DIB Lengths and Starting Coordinate
	DWORD	dwLen;
	DWORD	dwCompress;
	DWORD	iStartPos;

	// DIB
	BITMAP	DIBitmap;

	// DIB Information Header
	BITMAPINFOHEADER	BMIH;

	// Pointer to the DIB Information Header
	LPBITMAPINFOHEADER	lpBMIH;

	// DC Handle for the Region
	HDC		hMemDC;

	// Bitmap Handle to the Region
	HBITMAP	hDIBitmap;

	// Pointers to the Region Uncompressed DIB
	char	*pDIB;

	// Pointer to the Changes in the Region DIB
	char	*pDIBChange;
	char	*pDIBChangeStart;

	// Pointer to the Compressed Region DIB
	char	*pDIBCompress;

	// Pointer to the Global Region DIB
	char	*pDIBitmap;

	// DIB Flags
	BOOL	fDIBitmap;
	BOOL	fChange;
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