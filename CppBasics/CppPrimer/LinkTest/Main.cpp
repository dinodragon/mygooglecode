#include <iostream>
using namespace std;

//链表就地反转
struct Node
{
	int value;
	Node* next;

	Node( int v, Node* p ) : value(v), next(p) {}
};

void reverse( Node*& p )
{
	Node* t = 0;
	for( ; p ; )
	{
		Node* _t = t;
		t = p;
		p = p->next;
		t->next = _t;
	}
	p = t;
}

ostream& operator<<( ostream& os, const Node* p )
{
	os << '[';
	if( p ) { os << p->value; p=p->next; }
	for( ; p; p=p->next ) os << ',' << p->value;
	os << ']';
	return os;
}

int main(int argc, char* argv[])
{
	float a=1.0f;
	cout<<(int)a<<endl;
	cout<<(int&)a<<endl;

	//int *piPointer;
	//char cItem;
	//cItem='a';
	//piPointer=(int *)&cItem;
	//*piPointer=1298;


	//Node* p = new Node( 0, new Node( 1, new Node( 2, new Node( 3, new Node( 4, new Node( 5, 0 ) ) ) ) ) );
	//cout << p << endl;
	//reverse( p );
	//cout << p << endl;
	return 0;
}
