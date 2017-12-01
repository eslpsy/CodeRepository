#ifndef __I_ARRAY_HPP__
#define __I_ARRAY_HPP__

#include <cassert>

template<typename T>
class IArray
{
public:
	IArray();
	~IArray();

	T & operator[](const size_t index);
	void operator=(const IArray<T> &other);

	void clear() { m_size = 0; }					// 清空数组
	void push_back(const T & value);				// 在最后插入一个元素
	void pop_back();						// 在最后删除一个元素
	void remove(const size_t index);				// 移除一个元素
	size_t size() const { return m_size; }				// 返回数组当前大小
	size_t capacity() const { return m_capacity; }			// 返回数组容量
	bool empty() const { return m_end_index == m_begin_index; }	// 检测数组是否为空

private:
	size_t m_size;		// 数组当前大小
	size_t m_capacity;	// 数组容量
	T *m_values;		// 数组
};

template<typename T>
IArray<T>::IArray() : m_size(0)
{
	const static int INIT_SIZE = 10;
	m_capacity = INIT_SIZE;
	m_values = new T[INIT_SIZE];
}

template<typename T>
IArray<T>::~IArray()
{
	delete[] m_values;
}

template <typename T>
T & IArray<T>::operator[](const size_t index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < m_size);
#endif

	if (index >= 0 && index < m_size)
	{
		return m_values[index];
	}

	else
	{
		static T value;
		return value;
	}
}

template <typename T>
void IArray<T>::operator=(const IArray<T>& other)
{
	int new_capacity = other.m_capacity;
	T *new_values = new T[new_capacity];

	delete[] this->m_values;

	this->m_size = other.m_size;
	this->m_capacity = other.m_capacity;

	for (int i = 0; i < static_cast<int>(this->m_size); ++i)
	{
		new_values[i] = other.m_values[i];
	}

	this->m_values = new_values;
}

template <typename T>
void IArray<T>::push_back(const T & value)
{
	if (m_size >= m_capacity)
	{
		int new_capacity = m_capacity * 2;
		T *new_values = new T[new_capacity];

		for (int i = 0; i < static_cast<int>(m_size); ++i)
		{
			new_values[i] = m_values[i];
		}

		delete[] m_values;
		m_capacity = new_capacity;
		m_values = new_values;
	}

	if (m_size < m_capacity)
	{
		m_values[m_size++] = value;
	}
}

template <typename T>
void IArray<T>::pop_back()
{
	if (m_size > 0)
	{
		--m_size;
	}
}

template <typename T>
void IArray<T>::remove(const size_t index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < m_size);
#endif

	if (index >= 0 && index < m_size)
	{
		for (size_t i = index; i < (m_size - 1); ++i)
		{
			m_values[i] = m_values[i + 1];
		}
		--m_size;
	}
}

#endif
