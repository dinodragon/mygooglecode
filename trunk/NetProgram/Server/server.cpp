//��һ���ļ�����ִ��,������ѡ���Ķ˿ڽ��м���,�ȴ����ӡ����Ӻ����յ���������ʾ�����߱��浽�ļ���


#include <winsock2.h>
#include <iostream>
#include <fstream>

using namespace std;

void main()
{
	SOCKET sock, clientSocket;                   //socket
	char szMsg[255] = "����һ����Ϣ��.";//�����͵��ֶ�
	u_short Port = 9592;
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
	cout<<"��ǰʹ�õ�socket�汾:"<<(int)LOBYTE(wsaData.wVersion )<<"."<<(int)HIBYTE( wsaData.wVersion )<<endl;

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

	myaddr.sin_port=htons(Port);
	bind(sock,(sockaddr*)&myaddr,sizeof(myaddr));

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

	sockaddr_in addrto; //�ͻ��˵ĵ�ַ��Ϣ
	int nlen = sizeof(addrto);
	unsigned int uIndex = 1;
	char buf[32768]="";	
	long number=0;
	int iResult = 0;

	//�������
	while(true)
	{
		cout<<"��ʼ��"<<Port<<"�˿ڵȴ�����"<<endl;
		clientSocket = accept(sock,(sockaddr*)&addrto,&nlen);

		if (clientSocket < 0)
		{
			cout<<"client socket error, exit!"<<endl;
			abort();
		}
		else
		{
			cout<<"������һ��socket����"<<endl;
		}
		
		//ofstream out("f:\\aa.txt",ios_base::binary | ios_base::trunc);
		while(true)
		{
			number++;
			cin>>buf;
			send(clientSocket,buf,strlen(buf),0);
			iResult = recv(clientSocket,buf,sizeof(buf)-1,0);
			if (iResult <= 0)
			{
				cout<<"�Է�Socket�رգ��ȴ���һ�����ӣ�"<<endl;
				break;
			}
			
			buf[iResult]='\0';
			cout<<"���յ�"<<iResult<<"�ֽ�"<<":"<<endl<<buf<<endl;
			//out.write((const char*)(&buf),iResult);
			//cin>>buf;
			//send(clientSocket,buf,sizeof(buf),0);

			//memset(buf,0,sizeof(buf));
		}
			cout<<endl;
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