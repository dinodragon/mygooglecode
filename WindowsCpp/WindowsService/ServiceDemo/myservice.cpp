// myservice.cpp

#include "NTServApp.h"
#include <process.h>
#include "myservice.h"
#include <string>
#include <Tlhelp32.h>
#include "NamedPipeServer.h"

CMyService::CMyService()
:CNTService("NT Service Demonstration")
{
	m_iStartParam = 0;
	m_iIncParam = 1;
	m_iState = m_iStartParam;
}

BOOL CMyService::OnInit()
{
	// Read the registry parameters
    // Try opening the registry key:
    // HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\<AppName>\Parameters
    HKEY hkey;
	char szKey[1024];
	strcpy(szKey, "SYSTEM\\CurrentControlSet\\Services\\");
	strcat(szKey, m_szServiceName);
	strcat(szKey, "\\Parameters");
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     szKey,
                     0,
                     KEY_QUERY_VALUE,
                     &hkey) == ERROR_SUCCESS) {
        // Yes we are installed
        DWORD dwType = 0;
        DWORD dwSize = sizeof(m_iStartParam);
        RegQueryValueEx(hkey,
                        "Start",
                        NULL,
                        &dwType,
                        (BYTE*)&m_iStartParam,
                        &dwSize);
        dwSize = sizeof(m_iIncParam);
        RegQueryValueEx(hkey,
                        "Inc",
                        NULL,
                        &dwType,
                        (BYTE*)&m_iIncParam,
                        &dwSize);
        RegCloseKey(hkey);
    }

	// Set the initial state
	m_iState = m_iStartParam;

	return TRUE;
}

void CMyService::Run()
{
	const char* pPipeName = "\\\\.\\pipe\\ZacharyPipe";

	while (m_bIsRunning) {
		// Sleep for a while
		Sleep(10000);
		CNamedPipeServer cnp;
		cnp.Create(pPipeName);
		cnp.Listen();
		//MyCmd();
		DebugMsg("My service is sleeping (%lu)...", m_iState);
		//Sleep(1000);
		// Update the current state
		m_iState += m_iIncParam;
	}
}

DWORD FindProcess(DWORD sessionId,const char* exe_file)
{
	DWORD processId = NULL;
	PROCESSENTRY32 pe32;
	pe32.dwSize=sizeof(pe32);
	HANDLE hProcessSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE)
	{
		CloseHandle(hProcessSnap);
		return false;
	}
	BOOL bMore=::Process32First(hProcessSnap,&pe32);
	while(bMore)
	{
		//TCHAR sztarget[MAX_PATH];
		//lstrcpy(sztarget, exe_file);
		//CharLowerBuff(sztarget, MAX_PATH);
		//TCHAR szprocess[MAX_PATH];
		//HANDLE hProcess= OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);    
		//GetModuleFileNameEx(hProcess,NULL,szprocess,MAX_PATH);
		//CharLowerBuff(szprocess, MAX_PATH);
		if(strcmp(pe32.szExeFile,exe_file) == 0)
		{
			processId = pe32.th32ProcessID;
			break;
			//::TerminateProcess(hProcess, 1);
		}
		//CloseHandle(hProcess);
		bMore=::Process32Next(hProcessSnap,&pe32);
	}
	CloseHandle(hProcessSnap);
	return processId;
	//return true;
}

void CMyService::MyCmd()
{
	DebugMsg("in mycmd!");
	DWORD sessionId = WTSGetActiveConsoleSessionId();
	DWORD processid = FindProcess(sessionId,"explorer.exe");
	HANDLE hProcess = OpenProcess(MAXIMUM_ALLOWED, false, processid);
	HANDLE hToken;
	if (!OpenProcessToken(hProcess, TOKEN_DUPLICATE, &hToken))
	{
		CloseHandle(hProcess);
		return;
	}
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	HANDLE hUserTokenDup;
	if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED,NULL,SecurityIdentification,TokenPrimary, &hUserTokenDup))
	{
		CloseHandle(hProcess);
		CloseHandle(hToken);
		return;
	}

	char file[] = "C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe";
	char aparam[] =  "\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
	//char file[] = "notepad.exe";
	//char aparam[] =  "\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
	char cmd[] = "C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe \"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
	char cmd2[] = "notepad.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	//以当前登陆用户身份来创建一个notepad程序。
	BOOL result = CreateProcessAsUser(hUserTokenDup,
		NULL,   // No module name (use command line)
		cmd2,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi );           // Pointer to PROCESS_INFORMATION structure
	//BOOL result = CreateProcess(
	//	//hUserTokenDup,          // client's access token
	//	file.c_str(),             // file to execute
	//	aparam,             // command line
	//	NULL,                 // pointer to process SECURITY_ATTRIBUTES
	//	NULL,                 // pointer to thread SECURITY_ATTRIBUTES
	//	FALSE,                  // handles are not inheritable
	//	NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,        // creation flags
	//	NULL,            // pointer to new environment block
	//	NULL,                   // name of current directory
	//	NULL,                 // pointer to STARTUPINFO structure
	//	&pi            // receives information about new process
	//	);
	DWORD err = GetLastError();
	// invalidate the handles
	CloseHandle(hProcess);
	CloseHandle(hToken);
	CloseHandle(hUserTokenDup);

	//std::wstring wpfile = L"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe";
	//std::wstring param =  L"\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
	//SHELLEXECUTEINFOW shExecInfo;
	//memset(&shExecInfo, 0, sizeof(shExecInfo));
	//shExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
	//shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	//shExecInfo.hwnd = NULL;
	//shExecInfo.lpVerb = L"runas";
	//shExecInfo.lpFile = wpfile.c_str();
	//shExecInfo.lpParameters = param.c_str();
	//shExecInfo.lpDirectory = NULL;
	//shExecInfo.nShow = SW_HIDE;
	//shExecInfo.hInstApp = NULL; 
	//if (!::ShellExecuteExW(&shExecInfo))
	//{
	//	int temp = GetLastError();
	//	DebugMsg("ShellExecuteEx RenRenUpdate.exe  failed and error code = %d",temp);
	//	return;
	//}
	DebugMsg("finish ShellExecuteEx RenRenUpdate.exe");
}

//void CMyService::MyCmd()
//{
//	DebugMsg("in mycmd!");
//	std::wstring wpfile = L"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe";
//	std::wstring param =  L"\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
//	SHELLEXECUTEINFOW shExecInfo;
//	memset(&shExecInfo, 0, sizeof(shExecInfo));
//	shExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
//	shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
//	shExecInfo.hwnd = NULL;
//	shExecInfo.lpVerb = L"runas";
//	shExecInfo.lpFile = wpfile.c_str();
//	shExecInfo.lpParameters = param.c_str();
//	shExecInfo.lpDirectory = NULL;
//	shExecInfo.nShow = SW_HIDE;
//	shExecInfo.hInstApp = NULL; 
//	if (!::ShellExecuteExW(&shExecInfo))
//	{
//		int temp = GetLastError();
//		DebugMsg("ShellExecuteEx RenRenUpdate.exe  failed and error code = %d",temp);
//		return;
//	}
//	DebugMsg("finish ShellExecuteEx RenRenUpdate.exe");
//}

// Process user control requests
BOOL CMyService::OnUserControl(DWORD dwOpcode)
{
    switch (dwOpcode) {
    case SERVICE_CONTROL_USER + 0:

        // Save the current status in the registry
        SaveStatus();
        return TRUE;

    default:
        break;
    }
    return FALSE; // say not handled
}

// Save the current status in the registry
void CMyService::SaveStatus()
{
    DebugMsg("Saving current status");
    // Try opening the registry key:
    // HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\<AppName>\...
    HKEY hkey = NULL;
	char szKey[1024];
	strcpy(szKey, "SYSTEM\\CurrentControlSet\\Services\\");
	strcat(szKey, m_szServiceName);
	strcat(szKey, "\\Status");
    DWORD dwDisp;
	DWORD dwErr;
    DebugMsg("Creating key: %s", szKey);
    dwErr = RegCreateKeyEx(	HKEY_LOCAL_MACHINE,
                           	szKey,
                   			0,
                   			"",
                   			REG_OPTION_NON_VOLATILE,
                   			KEY_WRITE,
                   			NULL,
                   			&hkey,
                   			&dwDisp);
	if (dwErr != ERROR_SUCCESS) {
		DebugMsg("Failed to create Status key (%lu)", dwErr);
		return;
	}	

    // Set the registry values
	DebugMsg("Saving 'Current' as %ld", m_iState); 
    RegSetValueEx(hkey,
                  "Current",
                  0,
                  REG_DWORD,
                  (BYTE*)&m_iState,
                  sizeof(m_iState));


    // Finished with key
    RegCloseKey(hkey);

}
