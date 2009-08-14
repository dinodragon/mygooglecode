#include <iostream>
#include "main.h"

using namespace std;

void main()
{
	IXMLDOMDocumentPtr XMLFile = NULL; 
	IXMLDOMElement * XMLRoot = NULL; 

	if(FAILED(CoInitialize(NULL)))
	{
		cout<<"CoInitialize failed"<<endl;
	}
	if(FAILED(XMLFile.CreateInstance("MsXML2.DOMDocument.4.0")))
	{
		cout<<"CreateInstance failed"<<endl;
	}

	_variant_t varXML(L"..\\CallMSXML\\test.XML");
	VARIANT_BOOL varOut; 
	XMLFile->load(varXML, &varOut);
	XMLFile->get_documentElement(&XMLRoot); 
	IXMLDOMNodeList* XMLChildNodes = NULL;
	XMLRoot->get_childNodes(&XMLChildNodes);
	long len = 0;
	XMLChildNodes->get_length(&len);
	cout<<len<<endl;
	XMLRoot->Release();
	XMLFile.Release();
}