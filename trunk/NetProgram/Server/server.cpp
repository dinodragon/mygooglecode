//这一个文件即可执行,他会在选定的端口进行监听,等待连接。连接后会把收到的数据显示，或者保存到文件。


#include <winsock2.h>
#include <iostream>
#include <fstream>

using namespace std;

void main()
{
	SOCKET sock, clientSocket;                   //socket
	char szMsg[255] = "这是一个消息包.";//被发送的字段
	u_short Port = 9592;
	//1.启动SOCKET库，版本为2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;	
	wVersionRequested = MAKEWORD( 2, 0 );	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		cout<<"Socket2.0初始化失败，Exit!";
		return;
	}	
	cout<<"当前使用的socket版本:"<<(int)LOBYTE(wsaData.wVersion )<<"."<<(int)HIBYTE( wsaData.wVersion )<<endl;

	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 0 ) 
	{
		WSACleanup( );
		return; 
	}
	
	//2.创建socket，
	sock = socket(
		AF_INET,           //internetwork: UDP, TCP, etc
		SOCK_STREAM,        //SOCK_STREAM说明是TCP socket
		0                  //protocol
		);
	
	if (sock == INVALID_SOCKET ) 
	{
		cout<<"Socket 创建失败，Exit!";
		return;
	}
	
	//3.bind套接字，相当于给本地套接字赋值
	sockaddr_in myaddr; 
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	//myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	myaddr.sin_port=htons(Port);
	bind(sock,(sockaddr*)&myaddr,sizeof(myaddr));

	//5.listen 另一端的socket
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
	
	//6. accept 对方连接

	sockaddr_in addrto; //客户端的地址信息
	int nlen = sizeof(addrto);
	unsigned int uIndex = 1;
	char buf[32768]="";	
	long number=0;
	int iResult = 0;

	//服务程序
	while(true)
	{
		cout<<"开始在"<<Port<<"端口等待连接"<<endl;
		clientSocket = accept(sock,(sockaddr*)&addrto,&nlen);

		if (clientSocket < 0)
		{
			cout<<"client socket error, exit!"<<endl;
			abort();
		}
		else
		{
			cout<<"接收了一个socket连接"<<endl;
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
				cout<<"对方Socket关闭，等待下一个连接！"<<endl;
				break;
			}
			
			buf[iResult]='\0';
			cout<<"共收到"<<iResult<<"字节"<<":"<<endl<<buf<<endl;
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