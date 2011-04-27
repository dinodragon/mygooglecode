#include <winsock2.h>
#include <iostream>

using namespace std;

void main()
{
	SOCKET sock, clientSocket;                   //socket
	char szMsg[255] = "����һ����Ϣ��.";//�����͵��ֶ�
	
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
	cout<<(int)LOBYTE(wsaData.wVersion )<<"."<<(int)HIBYTE( wsaData.wVersion )<<endl;

	cout<<(int)LOBYTE(wsaData.wHighVersion )<<"."<<(int)HIBYTE( wsaData.wHighVersion )<<endl;

	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 0 ) 
	{
		WSACleanup( );
		return; 
	}
	
	//2.����socket��
	sock = socket(
		AF_INET,           //internetwork: UDP, TCP, etc
		SOCK_STREAM,        //SOCK_STREAM˵����TCP socket
		0                  //protocol
		);
	
	if (sock == INVALID_SOCKET ) 
	{
		cout<<"Socket ����ʧ�ܣ�Exit!";
		return;
	}
	
	//3.bind�׽��֣��൱�ڸ������׽��ָ�ֵ
	sockaddr_in myaddr; 
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	//myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	myaddr.sin_port=htons(7861);
	bind(sock,(sockaddr*)&myaddr,sizeof(myaddr));

	//4.���÷����ĵ�ַ
	sockaddr_in addrto;            //�����ĵ�ַ	
	//memset(&addrto,0,sizeof(addrto));
	//addrto.sin_family=AF_INET;
 //   addrto.sin_addr.s_addr=inet_addr("127.0.0.1");
	//�˿ںű���ͷ������󶨵Ķ˿ں�һ��
	//addrto.sin_port=htons(7861);
	
	//5.listen ��һ�˵�socket
	if (listen(sock,5) == SOCKET_ERROR )
	{
		closesocket(sock);
		WSACleanup();
		abort();
	}
	else
	{
		cout<<"listen succeed!"<<endl;
	}
	
	//6. accept �Է�����


	int nlen = sizeof(addrto);
	clientSocket = accept(sock,(sockaddr*)&addrto,&nlen);
	if (clientSocket < 0)
	{
		cout<<"client socket error, exit!"<<endl;
		abort();
	}
	else
	{
		cout<<"accepted client socket!"<<endl;
	}
	
	unsigned int uIndex = 1;
	char buf[256]="";	
	long number=0;

	int iResult = 0;

	while(true)
	{
		Sleep(1000);

		cin>>szMsg;

		if( send(clientSocket, szMsg, strlen(szMsg), 0)	== SOCKET_ERROR )
			cout<<"error, error id = "<<WSAGetLastError()<<endl;
		else
			cout<<uIndex++<<":an UDP package is sended."<<endl;

		//iResult = recv(clientSocket,buf,sizeof(buf),0);
		//if (iResult < 0)
		//{
		//	cout<<"����Socket�رգ��˳���"<<endl;
		//	//break;
		//}
		//else
		//cout<<number<<":"<<buf<<endl;
		//memset(buf,0,sizeof(buf));
	}
	
	if (!closesocket(sock)) 
	{
		cout<<WSAGetLastError()<<endl;
		return;
	}
	if (!closesocket(clientSocket)) 
	{
		cout<<WSAGetLastError()<<endl;
		return;
	}
	if (!WSACleanup()) 
	{
		cout<<WSAGetLastError()<<endl;;
		return;
	}	
}