//
// Templates.cpp
//

#include <iostream>

using namespace std;

template <typename T,size_t sSize =100>
class Stack
{
public:
	Stack()
	{ 
		m_sPos = 0;
	}
	~Stack() {}

	void Push( T value );

	T Pop();

	bool IsEmpty()
	{
		return( m_sPos == 0 );
	};
	bool HasElements()
	{
		return( m_sPos != 0 );
	}
	bool IsFull()
	{
		return( m_sPos == sSize );
	}
	long GetSize()
	{
		return sSize;
	}

private:
	//static const short sSize = 100;
	T m_data[ sSize ];
	short m_sPos;
};

//成员实现代码外置
//模板参数默认值只在类定义时定义一次，后面不能重复定义
template <typename T,size_t sSize>
void Stack<T,sSize>::Push( T value )
{
	m_data[ m_sPos++ ] = value;
	sSize;
}

template <typename T,size_t sSize>
T Stack<T,sSize>::Pop()
{
	return m_data[ --m_sPos ];
}


template <typename Type>
Type MAX( Type a, Type b )
{
	if ( a > b )
		return a;
	else
		return b;    
}

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

	return 0;
}