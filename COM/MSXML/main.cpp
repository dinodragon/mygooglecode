#import <msxml.dll>      //利用MSXML解析XML文件以及生成XML文件
#include <iostream>

using namespace MSXML;
using namespace std;


int main(int argc, TCHAR * argv[])
{
	MSXML::IXMLDOMDocumentPtr pXmlDoc;
	MSXML::IXMLDOMElementPtr pXmlRoot;
	CoInitialize(NULL);
	//创建DOMDocument对象
	HRESULT hr = pXmlDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
	
	if(!SUCCEEDED(hr)) 
	{         
		return 0;
	}

	argv[1] = TEXT("ASKLog.xml");  //XML文件的地址，存放于命令行参数

	pXmlDoc->load(argv[1]); //加载XML文件
	pXmlRoot = pXmlDoc->documentElement; //获取root节点的指针，也就是xml文件中的Log节点

	MSXML::IXMLDOMNodeListPtr pNodeList = pXmlRoot->childNodes;//获取指向Root节点子节点的指针数组，也就是获得
	//指向所有LogNode节点的指针
	MSXML::IXMLDOMNodeListPtr pNextNodeList = pNodeList->item[0]->childNodes; //获取第一个LogNode节点的所有子节点的
	//指针数组，也就是RecordTime，RecordState和RecordMessage
	//节点的指针
	cout<< pNextNodeList->item[0]->text <<endl;  //这样就能输出第一个节点：RecordTime的值了(字符串)类型 

	

	/****************************************************************
		写操作
	*****************************************************************/


	MSXML::IXMLDOMElementPtr pXmlNewNode;

	pXmlDoc->raw_createElement((_bstr_t)(char*)"LogNode", &pXmlNewNode);  //创建节点LogNode，并获得指向它的指针pXmlNewNode
	pXmlRoot->raw_appendChild(pXmlNewNode,NULL);   //将创建的节点挂在Root节点的下面
	//这里需要注意的是，假如ASKLog.xml文件不存在或为空，需要我们创建，需要使用如下代码
	pXmlDoc->raw_createElement((_bstr_t)(char*)"Log", &pXmlRoot);        //创建Root节点Log，并获得指向它的指针pXmlRoot
	pXmlDoc->raw_appendChild(pXmlRoot, NULL);                  //将pXmlRoot挂在pXmlDoc下面

	MSXML::IXMLDOMElementPtr pChildNode;

	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordTime", &pChildNode); //创建节点RecordTime，并获得指向它的指针pChildNode
	pChildNode->Puttext(TEXT("2007-11-29 16:29:30"));    //设置节点的值，使用Puttext方法
	pXmlNewNode->raw_appendChild(pChildNode,NULL);  //将创建的节点挂在新的上层节点pXmlNewNode下面


	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordState", &pChildNode);  //创建节点RecordState，并获得指向它的指针pChildNode
	pChildNode->Puttext("Running");      //设置节点的值，使用Puttext方法
	pXmlNewNode->raw_appendChild(pChildNode,NULL);//将创建的节点挂在新的上层节点pXmlNewNode下面

	pXmlDoc->raw_createElement((_bstr_t)(char*)"RecordMessage", &pChildNode);  //创建节点RecordMessage，并获得指向它的指针pChildNode
	pChildNode->Puttext("Finished level2 loop");   //设置节点的值，使用Puttext方法
	pXmlNewNode->raw_appendChild(pChildNode,NULL);//将创建的节点挂在新的上层节点pXmlNewNode下面

	pXmlDoc->save(argv[1]); //存储XML文件，如果存在就覆盖，不存在就创建
}