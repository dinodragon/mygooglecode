#include "Gdi.h"
#include "Server.h"
#include <windows.h>

// Add an Element to the Gdi Linked List
struct GdiList *Add_Gdi(struct GdiList *pNode,struct GdiDS Gdi)
{
	// Add an Item at the End of the List
	if (pNode->pNext = (struct GdiList *)malloc(sizeof(struct GdiList)))
	{
		// Move to the Created Node
		pNode = pNode->pNext;

		// Set the Grid Coordinates
		pNode->Gdi.iGridX = Gdi.iGridX;
		pNode->Gdi.iGridY = Gdi.iGridY;

		// Set the Rectangular Coordinates of the Region
		pNode->Gdi.iWidth1 = Gdi.iWidth1;
		pNode->Gdi.iWidth2 = Gdi.iWidth2;
		pNode->Gdi.iHeight1 = Gdi.iHeight1;
		pNode->Gdi.iHeight2 = Gdi.iHeight2;

		// Set the Number of Colors in the DIB Color Table
		pNode->Gdi.nColors = Gdi.nColors;

		// Set the Number of Bytes in the DIB Information Header
		pNode->Gdi.dwBitMapHeader = Gdi.dwBitMapHeader;

		// Bitmap Lengths and Starting Coordinate
		pNode->Gdi.dwLen = Gdi.dwLen;
		pNode->Gdi.dwCompress = Gdi.dwCompress;
		pNode->Gdi.iStartPos = Gdi.iStartPos;

		// Set the Device Independant Bitmap
		pNode->Gdi.DIBitmap = Gdi.DIBitmap;

		// Set the Device Independent Bitmap Information Header
		pNode->Gdi.BMIH = Gdi.BMIH;

		// Set the Pointer to the Device Independant Bitmap Information Header
		pNode->Gdi.lpBMIH = Gdi.lpBMIH;

		// DC Handle for the Region
		pNode->Gdi.hMemDC = Gdi.hMemDC;

		// Bitmap Handle to the Region
		pNode->Gdi.hDIBitmap = Gdi.hDIBitmap;

		// Pointer to the Region Uncompressed DIB
		pNode->Gdi.pDIB = Gdi.pDIB;

		// Pointer to the Changes in the Region DIB
		pNode->Gdi.pDIBChange = Gdi.pDIBChange;

		// Pointer to the Compressed Region DIB
		pNode->Gdi.pDIBCompress = Gdi.pDIBCompress;

		// Pointer to the Global Region Bitmap
		pNode->Gdi.pDIBitmap = Gdi.pDIBitmap;

		// Region Bitmap Flag
		pNode->Gdi.fDIBitmap = Gdi.fDIBitmap;
		pNode->Gdi.fChange = Gdi.fChange;

		pNode->pNext = NULL;
		return pNode;
	}
	return NULL;
}

// Completely clear the Gdi Linked List
void Clear_Gdi(struct GdiList *pStart)
{
	struct	GdiList	*pPrev;
	struct	GdiList	*pNode;
	while (pNode = pStart->pNext)
	{
		// Point to the Start of the List
		pPrev = pStart;

		// Link with the Node after the Current Node
		pPrev->pNext = pNode->pNext;

		// Delete the Memory DC
		DeleteDC(pNode->Gdi.hMemDC);

		// Delete the Bitmap Object
		DeleteObject(pNode->Gdi.hDIBitmap);

		// Free the Memory Associated w/ the Bitmap
		if (pNode->Gdi.fDIBitmap)
		{
			free(pNode->Gdi.pDIBitmap);
			free(pNode->Gdi.pDIB);
			free(pNode->Gdi.pDIBChangeStart);
		}

		// Delete the Current Node
		free(pNode);
	}
}