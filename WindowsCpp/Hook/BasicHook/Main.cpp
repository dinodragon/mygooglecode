#include <stdio.h>
#include <windows.h>
#include <Dbghelp.h>
#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib,"User32.lib")

//一个Windows API拦截的例子

typedef int (__stdcall *OLD_MessageBox)( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption,UINT uType );
OLD_MessageBox g_procOldMessageBox = NULL;


int __stdcall HOOK_MessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption,UINT uType)
{
	printf("%s\t%d\r\n",__FUNCTION__,__LINE__);
	if (NULL != g_procOldMessageBox)
		return g_procOldMessageBox(hWnd,lpText,"这是用hook替换的函数",uType); 
	else
		return MessageBox(hWnd,lpText,lpCaption,uType); ;
}

int replace_IAT(const char *pDllName,const char *pApiName,bool bReplace)
{
	HANDLE hProcess = ::GetModuleHandle (NULL);
	DWORD dwSize = 0;
	PIMAGE_IMPORT_DESCRIPTOR pImageImport = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hProcess,TRUE,
		IMAGE_DIRECTORY_ENTRY_IMPORT,&dwSize);
	if (NULL == pImageImport)
		return 1;
	PIMAGE_IMPORT_BY_NAME pImageImportByName = NULL;
	PIMAGE_THUNK_DATA  pImageThunkOriginal = NULL;
	PIMAGE_THUNK_DATA  pImageThunkReal  = NULL;
	while (pImageImport->Name)
	{
		if (0 == strcmpi((char*)((PBYTE)hProcess+pImageImport->Name),pDllName))
		{
			break;
		}
		++pImageImport;
	}
	if (! pImageImport->Name)
		return 2;
	pImageThunkOriginal = (PIMAGE_THUNK_DATA)((PBYTE)hProcess+pImageImport->OriginalFirstThunk  );
	pImageThunkReal = (PIMAGE_THUNK_DATA)((PBYTE)hProcess+pImageImport->FirstThunk   );
	while (pImageThunkOriginal->u1.Function)
	{
		if ((pImageThunkOriginal->u1 .Ordinal & IMAGE_ORDINAL_FLAG) != IMAGE_ORDINAL_FLAG)
		{
			pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hProcess+pImageThunkOriginal->u1 .AddressOfData );
			if (0 == strcmpi(pApiName,(char*)pImageImportByName->Name))
			{
				MEMORY_BASIC_INFORMATION mbi_thunk;
				VirtualQuery(pImageThunkReal, &mbi_thunk, sizeof(MEMORY_BASIC_INFORMATION)); 
				VirtualProtect(mbi_thunk.BaseAddress,mbi_thunk.RegionSize, PAGE_READWRITE, &mbi_thunk.Protect); 
				if (true == bReplace)
				{
					g_procOldMessageBox =(OLD_MessageBox) pImageThunkReal->u1.Function; 
					pImageThunkReal->u1.Function = (DWORD)HOOK_MessageBox;
				}
				else
					pImageThunkReal->u1.Function = (DWORD)g_procOldMessageBox;
				DWORD dwOldProtect; 
				VirtualProtect(mbi_thunk.BaseAddress, mbi_thunk.RegionSize, mbi_thunk.Protect, &dwOldProtect); 
				break;
			}
		}
		++pImageThunkOriginal;
		++pImageThunkReal;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	replace_IAT("User32.dll","MessageBoxA",true);
	MessageBox(NULL,"EnumIAT User32.dll MessageBoxA true;","",MB_OK);

	replace_IAT("User32.dll","MessageBoxA",false);
	MessageBox(NULL,"EnumIAT User32.dll MessageBoxA false;","",MB_OK);
	return 0;
}
