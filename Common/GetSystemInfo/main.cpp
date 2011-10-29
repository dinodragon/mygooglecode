#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>


using namespace std;

void systemInfo()
{
	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo); 

	// Display the contents of the SYSTEM_INFO structure. 

	printf("Hardware information: \n");  
	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n", 
		siSysInfo.dwNumberOfProcessors); 
	printf("  Page size: %u\n", siSysInfo.dwPageSize); 
	printf("  Processor type: %u\n", siSysInfo.dwProcessorType); 
	printf("  Minimum application address: %lx\n", 
		siSysInfo.lpMinimumApplicationAddress); 
	printf("  Maximum application address: %lx\n", 
		siSysInfo.lpMaximumApplicationAddress); 
	printf("  Active processor mask: %u\n", 
		siSysInfo.dwActiveProcessorMask); 
}

void mouseInfo()
{
	BOOL fResult;
	int aMouseInfo[3];

	fResult = GetSystemMetrics(SM_MOUSEPRESENT); 

	if (fResult == 0) 
		printf("No mouse installed.\n"); 
	else 
	{ 
		printf("Mouse installed.\n");

		// Determine whether the buttons are swapped. 

		fResult = GetSystemMetrics(SM_SWAPBUTTON); 

		if (fResult == 0) 
			printf("Buttons not swapped.\n"); 
		else printf("Buttons swapped.\n");

		// Get the mouse speed and the threshold values. 

		fResult = SystemParametersInfo(
			SPI_GETMOUSE,  // get mouse information 
			0,             // not used 
			&aMouseInfo,   // holds mouse information 
			0);            // not used 

		if( fResult )
		{ 
			printf("Speed: %d\n", aMouseInfo[2]); 
			printf("Threshold (x,y): %d,%d\n", 
				aMouseInfo[0], aMouseInfo[1]); 
		}
	} 
}

void ParaInfo()
{
	BOOL fResult;
	int aMouseInfo[3];       // array for mouse information

	// Get the current mouse speed. 

	fResult = SystemParametersInfo(
		SPI_GETMOUSE,   // get mouse information 
		0,              // not used 
		&aMouseInfo,    // holds mouse information
		0);             // not used 

	// Double it. 

	if( fResult )
	{
		aMouseInfo[2] = 2 * aMouseInfo[2]; 

		// Change the mouse speed to the new value. 

		SystemParametersInfo(
			SPI_SETMOUSE,      // set mouse information
			0,                 // not used 
			aMouseInfo,        // mouse information 
			SPIF_SENDCHANGE);  // update win.ini 
	}
}


int main()
{
	OSVERSIONINFOEX ifo;
	ifo.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&ifo);

	DWORD a=ifo.dwBuildNumber;
	DWORD b=ifo.dwMajorVersion;
	DWORD c=ifo.dwMinorVersion;
	DWORD d=ifo.dwOSVersionInfoSize;
	DWORD e=ifo.dwPlatformId;
	wstring f=ifo.szCSDVersion;

	TCHAR buf[100];
	swprintf_s(buf,sizeof(buf)/sizeof(TCHAR),TEXT("%d,%d,%d,%d,%d,%s"),a,b,c,d,e,f.c_str());
	//str.Format();
	//MessageBox(NULL,buf,TEXT("T"),MB_OK);
	wcout<<buf<<endl;

	systemInfo();
	mouseInfo();
	ParaInfo();

	return 0;
}