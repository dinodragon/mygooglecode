//
// Templates.cpp
//

#include <iostream>
#include "max.h"
#include "Stack.h"
#include "Inheritance.h"

using namespace std;

int main( int argc, char *argv[] )
{
	// Function templates
	int    iMax = MAX<int>( 10, 12 );
	cout << "MAX( 10, 12 ) is " << iMax << endl;
	long   lMax = MAX<long>( 10, 12 );
	cout << "MAX( 10, 12 ) is " << lMax << endl;
	double dMax = MAX<double>( 10.0, 12.0 );
	cout << "MAX( 10.0, 12.0 ) is " << dMax << endl;


	Stack< int > intStack;
	Stack< int ,10> intStack10;

	// A dynamically created stack
	Stack<long>* plongStack = new Stack<long>;
	plongStack->Push( 1000 );
	plongStack->Push( 2000 );
	delete plongStack;

	intStack.Push( 100 );
	intStack.Push( 200 );
	intStack.Push( 300 );

	while( intStack.HasElements() )
	{
		cout << intStack.Pop() << endl;
	}

	Stack< double > doubleStack;
	Stack< double ,20> doubleStack20;

	cout << "doubleStack20 size is " << doubleStack20.GetSize() << endl;

	doubleStack.Push( 1.1 );
	doubleStack.Push( 2.2 );
	doubleStack.Push( 3.3 );
	doubleStack.Push( 4.4 );
	while( doubleStack.HasElements() )
	{
		cout << doubleStack.Pop() << endl;
	}


	cout<<"---------------------------------------------"<<endl;

	CMath math;
	math.BaseMethod();
	((CBase)math).BaseMethod();

	//�û��Զ���CMath�࣬new CComObject<CMath>()������Ӧ�ķ����ͻ���õ�CMath�ķ���
	//
	//�൱��CMath���ǻ��࣬CComObjcet�����麯���Ļ��࣬
	//CMath��ָ��ת��CComObjcetָ�����Ե��õ�������CMath���е�����ʵ��
	CComObject<CMath> *pMath = new CComObject<CMath>();
	pMath->CallBaseMethod();
	delete pMath;

	return 0;
}