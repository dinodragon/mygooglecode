#include <iostream>

using namespace std;

typedef
struct _Node
{
	int value;
	_Node *next;
}Node,*PNode;


void showList(PNode head)
{
	PNode p = head;
	while(p != NULL)
	{
		cout<<p->value<<endl;
		p = p->next;
	}
}

void Reverse(PNode *pphead)
{
	PNode p = *pphead;
	PNode pPre = NULL;
	while(p != NULL)
	{
		PNode temp = p->next;
		p->next = pPre;
		pPre = p;
		p = temp;
	}
	*pphead = pPre;
}

void Delete(PNode *pphead)
{
	PNode p = *pphead;
	while(p != NULL)
	{
		PNode pNext = p->next;
		delete p;
		p = pNext;
	}
	*pphead = NULL;
}

int main()
{
	cout<<"help"<<endl;
	PNode p = new Node();
	p->value = 0;
	p->next = NULL;
	PNode Head = p;

	for(int i = 0;i<10;i++)
	{
		p->next = new Node();
		p->next->value = i;
		p = p->next;
	}
	p->next = NULL;
	//showList(Head);
	Reverse(&Head);
	showList(Head);
	Delete(&Head);
}
