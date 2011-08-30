#pragma once

template <typename T>
class MyStack
{
private:
	static const int maxSize = 80;
	T m_data[maxSize];
	int top; //栈顶元素位置，初始为-1，表示空栈

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
			throw "栈已空";
		}
	}
	MyStack(void):top(-1)
	{};

	~MyStack(void){};
};
