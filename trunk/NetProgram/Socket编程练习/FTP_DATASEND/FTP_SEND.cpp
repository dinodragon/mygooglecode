#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

DWORD WINAPI Fun2Proc(LPVOID lpParameter);
SOCKET sock;

void main(void)
{

	//1.����SOCKET�⣬�汾Ϊ2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	u_short Port = 4105;
	int err;	
	wVersionRequested = MAKEWORD( 2, 0 );	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		cout<<"Socket2.0��ʼ��ʧ�ܣ�Exit!";
		return;
	}	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 0 )
	{
		WSACleanup();
		return; 
	}

	//2.�����׽���
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET ) {
		cout<<"Socket ����ʧ�ܣ�Exit!";
		return;
	}

	//3.�����ַ

	sockaddr_in myaddr; 
	memset(&myaddr,0,sizeof(myaddr));  //��myaddr�ռ���ȫ����Ϊ0
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	//�˿ںű���Ϳͻ������Ķ˿ں�һ��
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
	char outBuf[256]="����һ�����ڲ��Ե��ı��ļ�!";
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
		//	cout<<"�����޷��أ�"<<endl;
		//}
		//cout<<number<<":"<<buf;

		//hThread1=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
		//CloseHandle(hThread1);

		gets_s(outBuf,255);
		strncat(outBuf,"\r\n",2);
		oResult = send(sock,outBuf,strlen(outBuf)+1,0);
		if (oResult >= 0)
		{
			//cout<<"�����ֽ�:"<<oResult<<endl;
			//break;
		}

		//memset(buf,0,sizeof(buf));
		memset(outBuf,0,sizeof(outBuf));
	}
	//outBuf = "����һ�����ڲ��Ե��ı��ļ�!";
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
			cout<<"�����޷��أ�"<<endl;
			return 0;
		}
		cout<<buf;
	memset(buf,0,sizeof(buf));
	}
}