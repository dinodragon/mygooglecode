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
