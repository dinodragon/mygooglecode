#include <iostream>
#include "ftpclient.h"

using namespace std;

void main()
{


nsFTP::CFTPClient ftpClient;
nsFTP::CLogonInfo logonInfo("localhost", 21, "anonymous", 
                                      "anonymous@user.com");

//// connect to server
//ftpClient.Login(logonInfo);
//
//// get directory listing
//nsFTP::TSpFTPFileStatusVector list;
//ftpClient.List("/", list);
//
//// iterate listing
//for( nsFTP::TSpFTPFileStatusVector::iterator it=list.begin(); 
//                                         it!=list.end(); ++it )
//    TRACE("\n%s", (*it)->Name().c_str());
//
//// do file operations
//ftpClient.DownloadFile("/pub/test.txt", "c:\\temp\\test.txt");
//
//ftpClient.UploadFile("c:\\temp\\test.txt", "/upload/test.txt");
//
//ftpClient.RenameFile("/upload/test.txt", "/upload/NewName.txt");
//
//ftpClient.Delete("/upload/NewName.txt");
//
//// disconnect
//ftpClient.Logout();
}