#import <msxml.dll>      //����MSXML����XML�ļ��Լ�����XML�ļ�
#include <iostream>

using namespace MSXML;
using namespace std;


int main(int argc, TCHAR * argv[])
{
	MSXML::IXMLDOMDocumentPtr pXmlDoc;
	MSXML::IXMLDOMElementPtr pXmlRoot;
	CoInitialize(NULL);
	//����DOMDocument����
	HRESULT hr = pXmlDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
	
	if(!SUCCEEDED(hr)) 
	{         
		return 0;
	}

	argv[1] = TEXT("ASKLog.xml");  //XML�ļ��ĵ�ַ������������в���

	pXmlDoc->load(argv[1]); //����XML�ļ�
	pXmlRoot = pXmlDoc->documentElement; //��ȡroot�ڵ��ָ�룬Ҳ����xml�ļ��е�Log�ڵ�

	MSXML::IXMLDOMNodeListPtr pNodeList = pXmlRoot->childNodes;//��ȡָ��Root�ڵ��ӽڵ��ָ�����飬Ҳ���ǻ��
	//ָ������LogNode�ڵ��ָ��
	MSXML::IXMLDOMNodeListPtr pNextNodeList = pNodeList->item[0]->childNodes; //��ȡ��һ��LogNode�ڵ�������ӽڵ��
	//ָ�����飬Ҳ����RecordTime��RecordState��RecordMessage
	//�ڵ��ָ��
	cout<< pNextNodeList->item[0]->text <<endl;  //�������������һ���ڵ㣺RecordTime��ֵ��(�ַ���)���� 

	

	/****************************************************************
		д����
	*****************************************************************/


	MSXML::IXMLDOMElementPtr pXmlNewNode;

	pXmlDoc->raw_createElement((_bstr_t)(char*)"LogNode", &pXmlNewNode);  //�����ڵ�LogNode�������ָ������ָ��pXmlNewNode
	pXmlRoot->raw_appendChild(pXmlNewNode,NULL);   //�������Ľڵ����Root�ڵ������
	//������Ҫע����ǣ�����ASKLog.xml�ļ������ڻ�Ϊ�գ���Ҫ���Ǵ�������Ҫʹ�����´���
	pXmlDoc->raw_createElement((_bstr_t)(char*)"Log", &pXmlRoot);        //����Root�ڵ�Log�������ָ������ָ��pXmlRoot
	pXmlDoc->raw_appendChild(pXmlRoot, NULL);                  //��pXmlRoot����pXmlDoc����

	MSXML::IXMLDOMElementPtr pChildNode;

	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordTime", &pChildNode); //�����ڵ�RecordTime�������ָ������ָ��pChildNode
	pChildNode->Puttext(TEXT("2007-11-29 16:29:30"));    //���ýڵ��ֵ��ʹ��Puttext����
	pXmlNewNode->raw_appendChild(pChildNode,NULL);  //�������Ľڵ�����µ��ϲ�ڵ�pXmlNewNode����


	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordState", &pChildNode);  //�����ڵ�RecordState�������ָ������ָ��pChildNode
	pChildNode->Puttext("Running");      //���ýڵ��ֵ��ʹ��Puttext����
	pXmlNewNode->raw_appendChild(pChildNode,NULL);//�������Ľڵ�����µ��ϲ�ڵ�pXmlNewNode����

	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordMessage", &pChildNode);  //�����ڵ�RecordMessage�������ָ������ָ��pChildNode
	pChildNode->Puttext("Finished level2 loop");   //���ýڵ��ֵ��ʹ��Puttext����
	pXmlNewNode->raw_appendChild(pChildNode,NULL);//�������Ľڵ�����µ��ϲ�ڵ�pXmlNewNode����

	pXmlDoc->save(argv[1]); //�洢XML�ļ���������ھ͸��ǣ������ھʹ���
}