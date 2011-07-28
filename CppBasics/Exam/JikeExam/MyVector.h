#pragma once

template <class T>
class MyVector
{
private:
	T* m_pointer;
	int m_size;
	int m_maxSize;
public:
	MyVector()
	{
		m_size = 0;
		m_maxSize = 20;
		m_pointer = new T[m_maxSize];
	}
	void push_back(T value)
	{
		if(m_size < m_maxSize)
		{
			m_pointer[m_size++] = value;
		}
	}

	void clear()
	{
		m_size = 0;
		delete[] m_pointer;
		m_pointer = new T[m_maxSize];
	}

	bool empty()
	{
		return m_size == 0;
	}
	int size();
	//ve
	~MyVector()
	{
		delete[] m_pointer;
	}
};