#pragma once

template <typename T>
class MyStack
{
private:
	static const int maxSize = 80;
	T m_data[maxSize];
	int top; //ջ��Ԫ��λ�ã���ʼΪ-1����ʾ��ջ

public:
	bool push(T data)
	{
		if (top + 1 < maxSize)
		{
			m_data[++top] = data;
			return true;
		}
		return false;
	}

	T pop()
	{
		if (top >= 0)
		{
			return m_data[top--];
		}
		else
		{
			throw "ջ�ѿ�";
		}
	}
	MyStack(void):top(-1)
	{};

	~MyStack(void){};
};
