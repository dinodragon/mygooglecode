#include <iostream>
#include "main.h"
#include <assert.h>

using namespace std;

void main()
{
	IXMLDOMDocumentPtr XMLFile = NULL; 
	IXMLDOMElement * XMLRoot = NULL; 
	IXMLDOMNodeList * XMLChildNodes = NULL;
	IXMLDOMNode * pRootNode= NULL;
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

	variant_t varXML(L"..\\CallMSXML\\test.XML");
	VARIANT_BOOL varOut;
	hr = XMLFile->load(varXML, &varOut);
	assert(SUCCEEDED(hr));
	hr = XMLFile->get_documentElement(&XMLRoot); 
	assert(SUCCEEDED(hr));

	hr = XMLFile->selectSingleNode(L"root/name",&pRootNode);
	assert(SUCCEEDED(hr));

	BSTR text = SysAllocStringLen(L"",100);
	hr = pRootNode->get_text(&text);
	wstring str = wstring(text);
	cout<<str.c_str()<<endl;
	assert(SUCCEEDED(hr));

	hr = XMLRoot->get_childNodes(&XMLChildNodes);
	assert(SUCCEEDED(hr));

	hr = XMLChildNodes->get_length(&len);
	assert(SUCCEEDED(hr));

	cout<<len<<endl;
	XMLRoot->Release();
	XMLFile.Release();
}