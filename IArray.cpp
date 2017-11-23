#include "IArray.hpp"
#include <cassert>

template <typename T, size_t MAX_SIZE>
T & IArray<T, MAX_SIZE>::operator[](const size_t index)
{
#ifdef _DEBUG
	assert(index >= m_begin_index && index < m_end_index && m_end_index < MAX_SIZE);
#endif

	if (index >= m_begin_index && index < m_end_index && index < MAX_SIZE)
	{
		return m_values[index];
	}
	
	else
	{
		static T value;
		return value;
	}
}

template <typename T, size_t MAX_SIZE>
void IArray<T, MAX_SIZE>::push_back(const T & value)
{
#ifdef _DEBUG
	assert(m_end_index >= m_begin_index && m_end_index < MAX_SIZE);
#endif

	if (m_end_index < MAX_SIZE)
	{
		m_values[m_end_index++] = value;
	}
}

template <typename T, size_t MAX_SIZE>
void IArray<T, MAX_SIZE>::pop_back()
{
	if (m_end_index > m_begin_index)
	{
		--m_end_index;
	}
}

template <typename T, size_t MAX_SIZE>
void IArray<T, MAX_SIZE>::remove(const size_t index)
{
#ifdef _DEBUG
	assert(index >= m_begin_index && index < m_end_index && m_end_index < MAX_SIZE);
#endif

	if (m_end_index > index)
	{
		for (size_t i = index; i < (m_end_index - 1); ++i)
		{
			m_values[i] = m_values[i + 1];
		}
		--m_end_index;
	}
}
