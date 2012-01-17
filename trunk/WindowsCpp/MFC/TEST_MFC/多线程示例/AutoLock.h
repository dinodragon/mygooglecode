#pragma once

template <typename T>
class CAutoLock
{
public:
	CAutoLock(T *pLock)
	{
		m_pLock=pLock;
		m_pLock->Lock();
	}
	~CAutoLock()
	{
		m_pLock->Unlock();
	}

private:
	T *m_pLock;
};