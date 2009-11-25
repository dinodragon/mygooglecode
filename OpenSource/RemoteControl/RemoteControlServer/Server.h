#if !defined(SERVER_H)
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
void memblast(void* dest,void* src,DWORD count);
#ifdef __cplusplus
extern "C" 
{
#endif
DWORD	WINAPI LoadWinsock(LPVOID lpParam);
void	DispatchWMMessage(char *szString);
DWORD	WINAPI ClientThread(LPVOID lpParam);
BOOL	Transmit(SOCKET MySocket,char *pData,DWORD iLength);
int		GetRegionDisplay(HWND hWnd);
void	SendResolution(SOCKET MySocket);
int		SendRegionDisplay(HWND hWnd,SOCKET MySocket);
void	InitDisplay(HWND hWnd);
void	ClearDisplay(HWND hWnd);
#ifdef __cplusplus
}
#endif
#endif