#include <winsock2.h>
#include <iostream>

using namespace std;

void main(void)
{
	SOCKET sock;
	
	//1.����SOCKET�⣬�汾Ϊ2.0
	WORD wVersionRequested;
	WSADATA wsaData;
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

//	struct sockaddr_in {
//        short   sin_family;
//        u_short sin_port;
//        struct  in_addr sin_addr;
//        char    sin_zero[8];
//};

	sockaddr_in myaddr; 
	memset(&myaddr,0,sizeof(myaddr));  //��myaddr�ռ���ȫ����Ϊ0
	myaddr.sin_family=AF_INET;
	
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	//�˿ںű���Ϳͻ������Ķ˿ں�һ��
	myaddr.sin_port=htons(21);

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
	
	char buf[256]="";	
	long number=0;
	int iResult = 0;
	while(true)
	{
		number++;
		iResult = recv(sock,buf,sizeof(buf),0);
		if (iResult < 0)
		{
			cout<<"����Socket�رգ��˳���"<<endl;
			//break;
		}
		Sleep(500);
		cout<<number<<":"<<buf<<endl;
		memset(buf,0,sizeof(buf));
	}

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
