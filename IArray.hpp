#ifndef __I_ARRAY_HPP__
#define __I_ARRAY_HPP__

template<typename T, size_t MAX_SIZE>
class IArray
{
public:
	IArray();
	IArray(size_t m_begin_index);

	T & operator[](const size_t index);

	void clear() { m_end_index = m_begin_index; }				        // 清空数组
	void push_back(const T & value);							              // 在最后插入一个元素
	void pop_back();											                      // 在最后删除一个元素
	void remove(const size_t index);							              // 移除一个元素
	size_t begin() const { return m_begin_index; }			        // 返回数组起始下标值
	size_t end() const { return m_end_index; }					        // 返回数组当前大小
	size_t max_size() const { return MAX_SIZE; }				        // 返回数组最大容量
	bool empty() const { return m_end_index == m_begin_index; }	// 检测数组是否为空
	bool full() const { return m_end_index == MAX_SIZE; }		    // 检测数组是否已满
	T * data() { return m_values; }								              // 返回数组指针

private:
	T m_values[MAX_SIZE];	// 数组
	size_t m_begin_index;	// 数组初始下标，某些情况下可能需要从T[1]开始存数据
	size_t m_end_index;		// 数组末尾下标
};

#endif
