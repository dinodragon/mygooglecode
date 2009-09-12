#include <iostream>
#include "main.h"
#include <assert.h>

using namespace std;

void main()
{
	IXMLDOMDocumentPtr XMLFile = NULL; 
	IXMLDOMElement * XMLRoot = NULL; 
	IXMLDOMNodeList * pNodeList = NULL;
	IXMLDOMNode * pNode= NULL;
	IXMLDOMNamedNodeMap * pNodeMap = NULL;
	long len = 0;
	HRESULT hr = S_FALSE;

	if(FAILED(CoInitialize(NULL)))
	{
		cout<<"CoInitialize failed"<<endl;
		return;
	}
	if(FAILED(XMLFile.CreateInstance("MSXML2.DOMDocument.4.0")))
	{
		cout<<"CreateInstance failed"<<endl;
		return;
	}

	//variant_t 是VARIANT的包装类
	variant_t varXML(L"..\\CallMSXML\\test.XML");
	VARIANT_BOOL varOut;
	hr = XMLFile->load(varXML, &varOut);
	assert(SUCCEEDED(hr));
	hr = XMLFile->get_documentElement(&XMLRoot); 
	assert(SUCCEEDED(hr));

	BSTR version = SysAllocString(L"");
	//VARIANT 是一种可存储多数类型的结构
	VARIANT verValue;
	hr = XMLRoot->getAttribute(L"version",&verValue);
	assert(SUCCEEDED(hr));
	wcout<<"Version:"<<wstring(verValue.bstrVal).c_str()<<endl;

	hr = XMLFile->selectSingleNode(L"root/Error",&pNode);
	assert(SUCCEEDED(hr));
	hr = pNode->get_attributes(&pNodeMap);
	assert(SUCCEEDED(hr));

	BSTR nodeName = SysAllocString(L"");
	BSTR text = SysAllocString(L"");
	hr = XMLFile->selectSingleNode(L"root/SessionId",&pNode);
	assert(SUCCEEDED(hr));
	hr = pNode->get_text(&text);
	assert(SUCCEEDED(hr));
	hr = pNode->get_nodeName(&nodeName);
	assert(SUCCEEDED(hr));
	wcout<<wstring(nodeName).c_str()<<":"<<wstring(text).c_str()<<endl;


	hr = XMLRoot->get_childNodes(&pNodeList);
	assert(SUCCEEDED(hr));

	hr = pNodeList->get_length(&len);
	assert(SUCCEEDED(hr));

	cout<<"ChildNodesLength:"<<len<<endl;
	XMLRoot->Release();
	XMLFile.Release();
}