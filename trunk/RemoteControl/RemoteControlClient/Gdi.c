#include "Gdi.h"
#include "Client.h"
#include <windows.h>

// Add an Element to the Gdi Linked List
struct GdiList *Add_Gdi(struct GdiList *pNode,struct GdiDS Gdi)
{
	// Add an Item at the End of the List
	if (pNode->pNext = (struct GdiList *)malloc(sizeof(struct GdiList)))
	{
		// Move to the Created Node
		pNode = pNode->pNext;

		// Pointer to the Global Region Bitmap
		pNode->Gdi.pDIBitmap = Gdi.pDIBitmap;

		// Pointer to the Received DIB
		pNode->Gdi.pDIB = NULL;
		pNode->Gdi.pStartDIB = NULL;

		// Grid Coordinates
		pNode->Gdi.iGridX = Gdi.iGridX;
		pNode->Gdi.iGridY = Gdi.iGridY;

		// Set the Rectangular Region
		pNode->Gdi.iWidth1 = Gdi.iWidth1;
		pNode->Gdi.iWidth2 = Gdi.iWidth2;
		pNode->Gdi.iHeight1 = Gdi.iHeight1;
		pNode->Gdi.iHeight2 = Gdi.iHeight2;

		// DIB Info header
		pNode->Gdi.lpBitmapIH = Gdi.lpBitmapIH;

		// Region Bitmap Flag
		pNode->Gdi.fDIBitmap = Gdi.fDIBitmap;

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

		// Free the Bitmap Data
		if (pNode->Gdi.fDIBitmap)
		{
			free(pNode->Gdi.pDIBitmap);
			free(pNode->Gdi.pDIB);
		}

		// Delete the Current Node
		free(pNode);
	}
}