// myservice.cpp

#include "NTServApp.h"
#include <process.h>
#include "myservice.h"
#include <string>

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
	MyCmd();
	while (m_bIsRunning) {
		// Sleep for a while
		DebugMsg("My service is sleeping (%lu)...", m_iState);
		Sleep(1000);
		// Update the current state
		m_iState += m_iIncParam;
	}
}

void CMyService::MyCmd()
{
	DebugMsg("in mycmd!");
	std::wstring wpfile = L"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe";
	std::wstring param =  L"\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_partial.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off";
	SHELLEXECUTEINFOW shExecInfo;
	memset(&shExecInfo, 0, sizeof(shExecInfo));
	shExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
	shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	shExecInfo.hwnd = NULL;
	shExecInfo.lpVerb = L"runas";
	shExecInfo.lpFile = wpfile.c_str();
	shExecInfo.lpParameters = param.c_str();
	shExecInfo.lpDirectory = NULL;
	shExecInfo.nShow = SW_HIDE;
	shExecInfo.hInstApp = NULL; 
	if (!::ShellExecuteExW(&shExecInfo))
	{
		int temp = GetLastError();
		DebugMsg("ShellExecuteEx RenRenUpdate.exe  failed and error code = %d",temp);
		return;
	}
	DebugMsg("finish ShellExecuteEx RenRenUpdate.exe");
}

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
