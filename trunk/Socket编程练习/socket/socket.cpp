#include <winsock2.h>
#include <iostream>

using namespace std;

void main()
{
	SOCKET sock; //socket�׽���
	char szMsg[] = "this is a UDP test package";//�����͵��ֶ�
	//1.����SOCKET�⣬�汾Ϊ2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 0 );
	err = WSAStartup(wVersionRequested,&wsaData);

	if ( 0 != err ) //���Socket��ʼ���Ƿ�ɹ�
	{
		cout<<"Socket2.0��ʼ��ʧ�ܣ�Exit!";
		return;
	}
	//���Socket��İ汾�Ƿ�Ϊ2.0

	if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
	{
		WSACleanup( );
		return;
	}

	//2.����socket��
	sock = socket(
		AF_INET, //internetwork: UDP, TCP, etc
		SOCK_DGRAM, //SOCK_DGRAM˵����UDP����
		0 //protocol
		);

	if (INVALID_SOCKET == sock ) {
		cout<<"Socket ����ʧ�ܣ�Exit!";
		return;
	}

	//3.���ø��׽���Ϊ�㲥���ͣ�

	bool opt = true;

	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char FAR *>(&opt), sizeof(opt));

	//4.���÷����ĵ�ַ

	sockaddr_in addrto; //�����ĵ�ַ

	memset(&addrto,0,sizeof(addrto));

	addrto.sin_family = AF_INET; //��ַ����Ϊinternetwork

	addrto.sin_addr.s_addr = INADDR_BROADCAST; //����ipΪ�㲥��ַ

	addrto.sin_port = htons(7861); //�˿ں�Ϊ7861

	int nlen=sizeof(addrto);

	unsigned int uIndex = 1;

	while(true)

	{
		Sleep(1000); //��������һ��
		//��㲥��ַ������Ϣ
		if( sendto(sock, szMsg, strlen(szMsg), 0, (sockaddr*)&addrto,nlen)
			== SOCKET_ERROR )
			cout<<WSAGetLastError()<<endl;
		else
			cout<<uIndex++<<":an UDP package is sended."<<endl;
	}

	if (!closesocket(sock)) //�ر��׽���
	{
		WSAGetLastError();
		return;
	}

	if (!WSACleanup()) //�ر�Socket��
	{
		WSAGetLastError();
		return;
	}
}
