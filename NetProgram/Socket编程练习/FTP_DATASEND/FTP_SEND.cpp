#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

DWORD WINAPI Fun2Proc(LPVOID lpParameter);
SOCKET sock;

void main(void)
{

	//1.启动SOCKET库，版本为2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	u_short Port = 4105;
	int err;	
	wVersionRequested = MAKEWORD( 2, 0 );	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		cout<<"Socket2.0初始化失败，Exit!";
		return;
	}	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 0 )
	{
		WSACleanup();
		return; 
	}

	//2.创建套接字
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET ) {
		cout<<"Socket 创建失败，Exit!";
		return;
	}

	//3.定义地址

	sockaddr_in myaddr; 
	memset(&myaddr,0,sizeof(myaddr));  //将myaddr空间内全部置为0
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	//端口号必须和客户发往的端口号一致
	myaddr.sin_port=htons(Port);

	//4.connect
	if (connect(sock,(sockaddr*)&myaddr,sizeof(myaddr)) == SOCKET_ERROR)
	{
		cout<<"connect failed, exit!"<<endl;
		closesocket(sock);
		WSACleanup();
		exit(1);
	}
	else
	{
		cout<<"connect succeed!"<<endl;
	}
	
	char buf[2048]="";
	char outBuf[256]="这是一个用于测试的文本文件!";
	long number=0;
	int iResult = 0,oResult=0;
	HANDLE hThread1;



		//hThread1=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
		//CloseHandle(hThread1);
	
		
		while(false)
	{
		//number++;
		//iResult = recv(sock,buf,sizeof(buf),0);
		//if (iResult < 0)
		//{
		//	cout<<"服务方无返回！"<<endl;
		//}
		//cout<<number<<":"<<buf;

		//hThread1=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
		//CloseHandle(hThread1);

		gets_s(outBuf,255);
		strncat(outBuf,"\r\n",2);
		oResult = send(sock,outBuf,strlen(outBuf)+1,0);
		if (oResult >= 0)
		{
			//cout<<"发送字节:"<<oResult<<endl;
			//break;
		}

		//memset(buf,0,sizeof(buf));
		memset(outBuf,0,sizeof(outBuf));
	}
	//outBuf = "这是一个用于测试的文本文件!";
	send(sock,outBuf,strlen(outBuf)+1,0);

	//Sleep(5000);
	if (!closesocket(sock)) 
	{
		WSAGetLastError();
		return;
	}

	if (!WSACleanup())
	{
		WSAGetLastError();
		return;
	}
}


DWORD WINAPI Fun2Proc( LPVOID lpParameter )
{
	Sleep(10);
	char buf[2048]="";
	int iResult = 0;
	while(true)
	{
		iResult = recv(sock,buf,sizeof(buf)-1,0);
		if (iResult <= 0)
		{
			cout<<"服务方无返回！"<<endl;
			return 0;
		}
		cout<<buf;
	memset(buf,0,sizeof(buf));
	}
}