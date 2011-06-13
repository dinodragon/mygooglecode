#include <stdio.h>
#include <iostream>
#include "..\tinyxml.h"

using namespace std;

int main()
{
	//const char* demoEnd =
	//	"<?xml version=\"1.0\" standalone=\"no\" ?>"
	//	"<!-- Our to do list data -->"
	//	"<ToDo>"
	//	"<!-- Do I need a secure PDA? -->"
	//	"<Item priority=\"2\" distance=\"close\">Go to the"
	//	"<bold>Toy store!"
	//	"</bold>"
	//	"</Item>"
	//	"<Item priority=\"1\" distance=\"far\">Talk to:"
	//	"<Meeting where=\"School\">"
	//	"<Attendee name=\"Marple\" position=\"teacher\" />"
	//	"<Attendee name=\"Voel\" position=\"counselor\" />"
	//	"</Meeting>"
	//	"<Meeting where=\"Lunch\" />"
	//	"</Item>"
	//	"<Item priority=\"2\" distance=\"here\">Do bills"
	//	"</Item>"
	//	"</ToDo>";
	//cout<<demoEnd<<endl;

	TiXmlDocument doc("demotest.xml");
	doc.LoadFile();
	//doc.Parse(demoEnd);
	TiXmlElement * root = doc.RootElement();
	TiXmlNode *fNode = root->FirstChild();
	
	TiXmlNode *lNode = root->LastChild();
	cout<<fNode->Value()<<endl;
	cout<<lNode->Value()<<endl;

	TiXmlNode *p = fNode;
	while(p != NULL)
	{
		cout<<p->Value()<<endl;
		p = p->FirstChild();
	}
	cout<<doc.Value()<<endl;
}

